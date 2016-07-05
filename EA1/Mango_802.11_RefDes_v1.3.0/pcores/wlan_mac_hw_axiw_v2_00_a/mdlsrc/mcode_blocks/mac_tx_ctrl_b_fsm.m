function [phy_tx_start, tx_done, tx_result_out, fsm_state_out] = ...
    mac_tx_ctrl_b_fsm(...
        pre_wait_postRxTimer1, ...
        pre_wait_postRxTimer2, ...
        pre_wait_postTxTimer1, ...
        req_zero_nav, ...
        reset, ...
        new_tx, ...
        nav_zero, ...
        postRxTimer1_done, ...
        postRxTimer2_done, ...
        postTxTimer1_done, ...
        phy_tx_done)

persistent fsm_state, fsm_state=xl_state(0, {xlUnsigned, 3, 0});
persistent tx_result, tx_result=xl_state(0, {xlUnsigned, 2, 0});

fsm_state_out = fsm_state;
tx_result_out = tx_result;

%Inputs:
% reset: synchronous reset, forces internal state variables back to default (IDLE state)
% new_tx: Software request for new Tx cycle
% pre_wait_postRxTimer1: Param requiring this Tx occur after postRxTimer 1 expires
% pre_wait_postRxTimer2: Param requiring this Tx occur after postRxTimer 2 expires
% pre_wait_postTxTimer1: Param requiring this Tx occur after postTxTimer 1 expires
% req_zero_nav: Param requiring this Tx be skipped if NAV is nonzero at Tx time
% nav_zero: Indication from MAC if NAV is currently zero (idle)
% postRxTimer1_done: Indication from MAC that postRx Timer 1 is done
% postRxTimer2_done: Indication from MAC that postRx Timer 2 is done
% postTxTimer1_done: Indication from MAC that postTx Timer 1 is done
% phy_tx_done: Indication from PHY that PHY Tx is done

%Outputs:
% backoff_start: Indication to MAC hw to run idle->backoff process
% phy_tx_start: Indication to PHY to start Tx
% tx_done: Indication to MAC hw that this Tx cycle is complete
% tx_result_out: Status of tx_done (did Tx or did not Tx)
% fsm_state_out: Value of  internal state register (for debugging)

%States:
% ST_IDLE: Waiting for new Tx from MAC sw
% ST_DO_TX: Started PHY Tx, waiting for completion
% ST_DEFERRING: Deferral required, wait for BO to finish
% ST_POST_TX: Finished Tx, waiting for timeout or Rx


ST_IDLE = 0;
ST_PRE_TX_WAIT = 1;
ST_CHECK_NAV = 2;
ST_DO_TX = 3;
ST_DONE = 4;

TX_RESULT_NONE = 0;
TX_RESULT_DID_TX = 1;
TX_RESULT_NO_TX = 2;

if(reset)
    phy_tx_start = 0;
    tx_done = 0;
    fsm_state = ST_IDLE;
    tx_result = TX_RESULT_NONE;

else
    switch double(fsm_state)

        case ST_IDLE
            phy_tx_start = 0;
            tx_done = 0;

            tx_result = TX_RESULT_NONE;

            if(new_tx)
                if(pre_wait_postRxTimer1 || pre_wait_postRxTimer2 || pre_wait_postTxTimer1)
                    %Tx scheduled for future, some fixed time after previous Tx/Rx
                    fsm_state = ST_PRE_TX_WAIT;
                else
                    %No waiting - move on to NAV check, then Tx
                    fsm_state = ST_CHECK_NAV;
                end
            else
                fsm_state = ST_IDLE;
            end

        case ST_PRE_TX_WAIT
            phy_tx_start = 0;
            tx_done = 0;

            tx_result = TX_RESULT_NONE;
            
            %Stay in PRE_TX_WAIT until the selected timer expires
            % MAC must take care if using multiple timers/conditions - only
            %  the first will trigger a Tx, the others will expire without effect
            if( (pre_wait_postRxTimer1 && postRxTimer1_done) || ...
                (pre_wait_postRxTimer2 && postRxTimer2_done) || ...
                (pre_wait_postTxTimer1 && postTxTimer1_done))
                fsm_state = ST_CHECK_NAV;
            else
                fsm_state = ST_PRE_TX_WAIT;
            end

        case ST_CHECK_NAV
            phy_tx_start = 0;
            tx_done = 0;

            if( (req_zero_nav && nav_zero) || ~req_zero_nav)
                %Either don't care about NAV, or NAV was zero - start Tx
                tx_result = TX_RESULT_DID_TX;
                fsm_state = ST_DO_TX;
            else
                %NAV was non-zero at Tx time - skip Tx
                tx_result = TX_RESULT_NO_TX;
                fsm_state = ST_DONE;
            end
            
        case ST_DO_TX
            phy_tx_start = 1;
            tx_done = 0;

            % Stay here until PHY Tx finishes
            if(phy_tx_done)
                fsm_state = ST_DONE;
            else
                fsm_state = ST_DO_TX;
            end

        case ST_DONE
            phy_tx_start = 0;
            tx_done = 1;

            %Previous state set tx_result - leave it alone so downstream
            % logic can latch it when tx_done goes high

            fsm_state = ST_IDLE;

        otherwise
            %This case should be impossible; mostly here to appease MATLAB
            phy_tx_start = 0;
            tx_done = 0;
            tx_result = TX_RESULT_NONE;
            fsm_state = ST_IDLE;

    end %end switch
end %end else

end %end function

