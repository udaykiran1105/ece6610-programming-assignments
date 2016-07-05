function [backoff_start, phy_tx_start, tx_done, tx_result_out, fsm_state_out] = ...
    mac_tx_ctrl_a_fsm(...
        pre_wait_postRxTimer1, ...
        pre_wait_postTxTimer1, ...
        post_wait_postTxTimer2, ...
        reset, ...
        new_tx, ...
        postRxTimer1_done, ...
        postTxTimer1_done, ...
        postTxTimer2_done, ...
        backoff_done, ...
        idle_for_difs, ...
        phy_tx_done, ...
        phy_rx_start)

persistent fsm_state, fsm_state=xl_state(0, {xlUnsigned, 3, 0});
persistent tx_result, tx_result=xl_state(0, {xlUnsigned, 2, 0});

fsm_state_out = fsm_state;
tx_result_out = tx_result;

%Inputs:
% reset: synchronous reset, forces internal state variables back to default (IDLE state)
% new_tx: Software request for new Tx cycle
% pre_wait_postRxTimer1: Param requiring this Tx occur after postRxTimer 1 expires
% pre_wait_postTxTimer1: Param requiring this Tx occur after postTxTimer 1 expires
% post_wait_postTxTimer2: Param requiring this Tx state wait after transmitting for postTxTimer 2 expiration
% backoff_done: Indication from MAC hw that backoff period is done
% idle_for_difs: Indication from MAC hw that medium has been idle > DIFS/EIFS
% phy_tx_done: Indication from PHY that last sample is transmitted
% phy_rx_start: Indication from PHY that new Rx has started

%Outputs:
% backoff_start: Indication to MAC hw to run idle->backoff process
% phy_tx_start: Indication to PHY to start Tx
% tx_done: Indication to MAC hw that this Tx cycle is complete
% tx_result_out: Status of tx_done (timeout or rx_started)
% fsm_state_out: Value of  internal state register (for debugging)

ST_IDLE = 0;
ST_PRE_TX_WAIT = 1;
ST_START_BO = 2;
ST_DEFER = 3;
ST_DO_TX = 4;
ST_POST_TX = 5;
ST_POST_TX_WAIT = 6;
ST_DONE = 7;

TX_RESULT_NONE = 0;
TX_RESULT_POSTTX_TIMER_EXPIRED = 1;
TX_RESULT_RX_STARTED = 2;

if(reset)
    backoff_start = 0;
    phy_tx_start = 0;
    tx_done = 0;
    fsm_state = ST_IDLE;
    tx_result = TX_RESULT_NONE;

else
    switch double(fsm_state)

        case ST_IDLE
            backoff_start = 0;
            phy_tx_start = 0;
            tx_done = 0;

            tx_result = TX_RESULT_NONE;

            if(new_tx)
                if(pre_wait_postRxTimer1 || pre_wait_postTxTimer1)
                    %Tx scheduled for future, some fixed time after previous Tx/Rx
                    fsm_state = ST_PRE_TX_WAIT;
                elseif(~backoff_done)
                    %If backoff is already running, use it as our deferral
                    fsm_state = ST_DEFER;
                elseif(idle_for_difs)
                    %If no pre-Tx BO is required, any old backoff has expired and medium has been idle,
                    % transmit immediately
                    fsm_state = ST_DO_TX;
                else
                    %If medium hasn't been idle, backoff
                    fsm_state = ST_START_BO;
                end
            else
                fsm_state = ST_IDLE;
            end

        case ST_PRE_TX_WAIT
            backoff_start = 0;
            phy_tx_start = 0;
            tx_done = 0;

            tx_result = TX_RESULT_NONE;
            
            %Stay in PRE_TX_WAIT until the selected timer expires
            % MAC must take care if using both timers/conditions - only
            %  the first will trigger a Tx, the other will expire without effect
            if( (pre_wait_postRxTimer1 && postRxTimer1_done) || (pre_wait_postTxTimer1 && postTxTimer1_done) )
                fsm_state = ST_DO_TX;
            else
                fsm_state = ST_PRE_TX_WAIT;
            end

        case ST_START_BO
            %Start the backoff counter, then transition to DEFER
            backoff_start = 1;
            phy_tx_start = 0;
            tx_done = 0;

            tx_result = TX_RESULT_NONE;
            fsm_state = ST_DEFER;

        case ST_DEFER
            backoff_start = 0;
            phy_tx_start = 0;
            tx_done = 0;

            tx_result = TX_RESULT_NONE;

            %Stay here until backoff completes
            if(backoff_done)
                fsm_state = ST_DO_TX;
            else
                fsm_state = ST_DEFER;
            end

        case ST_DO_TX
            backoff_start = 0;
            phy_tx_start = 1;
            tx_done = 0;

            tx_result = TX_RESULT_NONE;

            % Stay here until PHY Tx finishes
            if(phy_tx_done)
                fsm_state = ST_POST_TX;
            else
                fsm_state = ST_DO_TX;
            end

        case ST_POST_TX
            backoff_start = 0;
            phy_tx_start = 0;
            tx_done = 0;

            tx_result = TX_RESULT_NONE;

            %If post-Tx timer is selected, transition to wait state
            if(post_wait_postTxTimer2)
                fsm_state = ST_POST_TX_WAIT;
            else
                fsm_state = ST_DONE;
            end

        case ST_POST_TX_WAIT
            backoff_start = 0;
            phy_tx_start = 0;
            tx_done = 0;

            % Stay in POST_TX_WAIT until PHY Rx starts or the post-Tx
            %  timer expires. RX_START gets priority to handle unlikely
            %  case of RX_START and timer_done asserting in the same cycle
            if(phy_rx_start)
                fsm_state = ST_DONE;
                tx_result = TX_RESULT_RX_STARTED;
            elseif(postTxTimer2_done)
                fsm_state = ST_DONE;
                tx_result = TX_RESULT_POSTTX_TIMER_EXPIRED;
            else
                fsm_state = ST_POST_TX_WAIT;
                tx_result = TX_RESULT_NONE;
            end

        case ST_DONE
            backoff_start = 0;
            phy_tx_start = 0;
            tx_done = 1;

            %Previous state set tx_result - leave it alone so downstream
            % logic can latch it when tx_done goes high

            fsm_state = ST_IDLE;

        otherwise
            %This case should be impossible; mostly here to appease MATLAB
            backoff_start = 0;
            phy_tx_start = 0;
            tx_done = 0;
            tx_result = TX_RESULT_NONE;
            fsm_state = ST_IDLE;

    end %end switch
end %end else

end %end function

