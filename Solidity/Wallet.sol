// SPDX-License-Identifier: MIT

pragma solidity >0.8.0;

contract Sender {
    address payable _address;

    function setAddress(address payable a) public payable {
        _address = a;
    }

    function getAddress() public view returns(address) {
        return _address;
    }

    function defaultCall() public payable returns(bool) {
        (bool success,) = _address.call{value:1 ether}("");
        return success;
    }

    function fallbackCall() public payable returns(bool) {
        (bool success,) = _address.call{value:1 ether}("arr");
        return success;
    }

    function funcCall(uint _arg) public payable returns(bool) {
        (bool success,) = _address.call{value:1 ether}(
            abi.encodeWithSignature("func(uint256)", _arg)
        );
        
        return success;
    }
}

contract Receiver {
    enum State{DEFAULT, FALLBACK, RECEIVE, FUNC}

    State _state = State.DEFAULT;

    fallback() external payable { _state = State.FALLBACK; }
    receive() external payable { _state = State.RECEIVE; }

    function getState() public view returns(State) {
        return _state;
    }

    function func(uint _arg) public payable returns(uint) {
        _state = State.FUNC;
        return _arg;
    }
}

contract Wallet is Sender, Receiver {}
