// SPDX-License-Identifier: MIT

pragma solidity >0.8.0;

uint constant ETHER_TO_WEI = 1e18;

contract Asserter {

    uint private minuteAmount;

    constructor(uint _minutes) {
        minuteAmount = _minutes;
    }

    modifier checkCourse() {
        require(1 ether == ETHER_TO_WEI, "wei course is changed");
        _;
    }

    modifier checkMinute() {
        require((block.timestamp / 1 minutes) % minuteAmount == 0, "only works on minutes specified");
        _;
    }

    modifier checkGasLeft() {
        _;
        require(gasleft() > 1000, "You are running out of gas, reverting");
    }

    function foo() internal pure returns(int) {
        return 0;
    }

    function fooCourse() public payable checkCourse returns(int) {
        return foo();
    }

    function fooMinute() public view checkMinute returns(int) {
        return foo();
    }

    function fooGas() public view checkGasLeft returns(int) {
        return foo();
    }
}
