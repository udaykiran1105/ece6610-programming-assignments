# GROUP 1 - TCL SCRIPT - Default TCP implementation

#
# Initialize Global Variables
#
set ns_		[new Simulator]
set tracefd     [open pa2.tr w]
$ns_ trace-all $tracefd

set n1 [$ns_ node]
set n2 [$ns_ node]
set n3 [$ns_ node]

#Create a duplex link between the nodes
$ns_ duplex-link $n1 $n2 20Mb 2ms DropTail
# wireless link: bandwidth = 5Mbps, delay = 50ms
$ns_ duplex-link $n2 $n3 5Mb 50ms DropTail


#Create a TCP agent and attach it to node n1
set tcp1 [new Agent/TCP]
set sink1 [new Agent/TCPSink]
set telnet [new Application/Telnet]

$telnet set interval_ 0.002
$tcp1 set packetSize_ 1000

$ns_ attach-agent $n1 $tcp1
$ns_ attach-agent $n3 $sink1
$telnet attach-agent $tcp1

$ns_ connect $tcp1 $sink1

# the loss module (for wireless link)
set loss_rv [new RandomVariable/Uniform]
$loss_rv set min_ 0
$loss_rv set max_ 100

 set loss_module [new ErrorModel]
 $loss_module drop-target [new Agent/Null]
 $loss_module set rate_ 0.1 
 $loss_module ranvar $loss_rv

 $ns_ lossmodel $loss_module $n2 $n3

$ns_ at 0.0 "$telnet start"
$ns_ at 50.0 "$telnet stop"

$ns_ at 50.2 "$ns_ detach-agent $n1 $tcp1 ; $ns_ detach-agent $n3 $sink1"
$ns_ at 50.5 "finish"


proc finish {} {
    global ns_ tracefd
    $ns_ flush-trace
    close $tracefd
    exit 0
}

#Run the simulation
puts "Starting Simulation..."
$ns_ run



