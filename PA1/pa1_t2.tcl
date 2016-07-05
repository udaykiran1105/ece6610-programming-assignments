# Group 1
# tcl script file for TOPOLOGY 2

global rng rvstart sum lomo

# A random number generator with seed 0 - depends on system time
set rng [new RNG] 
$rng seed 0

# rvstart is used later to assign start and end times of simulation
set rvstart [new RandomVariable/Uniform]
$rvstart use-rng $rng

# ======================================================================
# Define options
# ======================================================================
set val(chan)           Channel/WirelessChannel    ;# channel type
set val(prop)           Propagation/TwoRayGround   ;# radio-propagation model
set val(netif)          Phy/WirelessPhy            ;# network interface type
set val(mac)            Mac/802_11                 ;# MAC type
set val(ifq)            Queue/DropTail/PriQueue    ;# interface queue type
set val(ll)             LL                         ;# link layer type
set val(ant)            Antenna/OmniAntenna        ;# antenna model
set val(ifqlen)         50                         ;# max packet in ifq
set val(nn)             3                          ;# number of mobilenodes
set val(rp)             DSR                        ;# routing protocol

# ======================================================================
# Main Program
# ======================================================================

# boundaries of topographical grid
set val(x)              500
set val(y)              500

# setting carrier sense threshold, transmitter power, channel data rate
Phy/WirelessPhy set CSThresh 1.7615e-10
Phy/WirelessPhy set Pt_ 0.282
Mac/802_11 set dataRate_ 1.0Mb
# To disable RTS/CTS - comment to enable
Mac/802_11 set RTSThreshold_ 4000

#
# Initialize Global Variables
#
set ns_		[new Simulator]
set tracefd     [open pa1_t2.tr w]
$ns_ trace-all $tracefd

# set up topography object
set topo [new Topography]
$topo load_flatgrid $val(x) $val(y)

#
# Create God
#
create-god $val(nn)

# configure node
# each node has an error model which generates random packet loss at the incoming interface

        $ns_ node-config -IncomingErrProc PacketErr \
		         -adhocRouting $val(rp) \
			 -llType $val(ll) \
			 -macType $val(mac) \
			 -ifqType $val(ifq) \
			 -ifqLen $val(ifqlen) \
			 -antType $val(ant) \
			 -propType $val(prop) \
			 -phyType $val(netif) \
			 -channelType $val(chan) \
			 -topoInstance $topo 			 	  

# Packet Error Model
proc PacketErr {} {
set err [new ErrorModel]
$err unit packet
$err set rate_ 0.0  # Loss-rate
return $err
}

set n1 [$ns_ node]
set n2 [$ns_ node]
set n3 [$ns_ node]

# making the wireless nodes fixed (not mobile)
$n1 random-motion 0
$n2 random-motion 0
$n3 random-motion 0


#
# Provide initial (X,Y) co-ordinates
#
$n1 set X_ 50.0
$n1 set Y_ 50.0

$n2 set X_ 250.0
$n2 set Y_ 50.0

$n3 set X_ 50.0
$n3 set Y_ 100.0

# UDP agents at nodes n1 and n3
set udp1 [new Agent/UDP]
$ns_ attach-agent $n1 $udp1
set udp2 [new Agent/UDP]
$ns_ attach-agent $n3 $udp2

# CBR traffic sources at nodes n1 and n3
set cbr1 [new Application/Traffic/CBR]
$cbr1 set packetSize_ 1500
$cbr1 set rate_ 500Kb
$cbr1 set random_ true
$cbr1 attach-agent $udp1

set cbr2 [new Application/Traffic/CBR]
$cbr2 set packetSize_ 1500
$cbr2 set rate_ 500Kb
$cbr2 set random_ true
$cbr2 attach-agent $udp2

# Loss Monitor at node n2
set lomo [new Agent/LossMonitor]
$ns_ attach-agent $n2 $lomo

# defining the connections among nodes in the topology
$ns_ connect $udp1 $lomo
$ns_ connect $udp2 $lomo

# setting simulation time and no. of simulations
set simtime 100.0
set sim_no 20

# loop assigns the start and stop times for each simulation
for {set j 1} {$j <= $sim_no} {incr j} {

set offset [expr [$rvstart value]]

# '105' is used to avoid overlap between current start and previous stop. Can be arbitrarily chosen above 101 
set temptime [expr $offset+(105*($j-1))] 
$ns_ at $temptime "$cbr1 start"
$ns_ at $temptime "$cbr2 start"
$ns_ at [expr $temptime+$simtime] "$cbr1 stop"
$ns_ at [expr $temptime+$simtime] "$cbr2 stop"

}
 # end of for loop for 20 simulations

# starting procedure for computing average throughput
$ns_ at [expr $sim_no*100+50] "record1"

proc record1 {} {
global lomo sim_no
# total bytes captured by loss monitor for 20 simulations
set bytes_rcvd [$lomo set bytes_]
set avg_throughput [expr ($bytes_rcvd*0.08)/$sim_no]
puts "Average UDP throughput for $sim_no simulations = $avg_throughput"
}

# resetting the nodes
$ns_ at [expr $sim_no*100+100] "$n1 reset"
$ns_ at [expr $sim_no*100+100] "$n2 reset"
$ns_ at [expr $sim_no*100+100] "$n3 reset"

$ns_ at [expr $sim_no*100+110] "stop"
$ns_ at [expr $sim_no*100+110] "puts \"NS EXITING...\" ; $ns_ halt"

proc stop {} {
    global ns_ tracefd
    $ns_ flush-trace
    close $tracefd
}

puts "Starting Simulation..."
$ns_ run
 













