// SPDX-License-Identifier: MIT

pragma solidity >0.8.0;

library SafeMath {
    function sub(uint256 a, uint256 b) internal pure returns (uint256) {
        assert(b <= a);
        return a - b;
    }

    function add(uint256 a, uint256 b) internal pure returns (uint256)   {
        uint256 c = a + b;
        assert(c >= a);
        return c;
    }
}

contract MaxCoin {
    using SafeMath for uint256;

    string private constant NAME = "MaxCoin";
    string private constant SYMBOL = "MCN";
    uint8 private constant DECIMALS = 0;
    uint private constant TOTAL_SUPPLY = 1e10;

    mapping(address => uint256) private balances;
    mapping(address => mapping(address => uint256)) private allowances;

    event Transfer(address indexed _from, address indexed _to, uint256 _value);
    event Approval(address indexed _owner, address indexed _spender, uint256 _value);

    constructor() {
        balances[msg.sender] = TOTAL_SUPPLY;
        emit Transfer(address(0x0), msg.sender, TOTAL_SUPPLY);
    }

    function name() public view returns (string memory) {
        return NAME;
    }

    function symbol() public view returns (string memory) {
        return SYMBOL;
    }

    function decimals() public view returns (uint8) { 
        return DECIMALS; 
    }

    function totalSupply() public view returns (uint256) { 
        return TOTAL_SUPPLY; 
    }

    function balanceOf(address _owner) public view returns (uint256 balance) { 
        return balances[_owner]; 
    }

    function transfer(address _to, uint256 _value) public returns (bool success) {
        balances[msg.sender] = balances[msg.sender].sub(_value);
        balances[_to] = balances[_to].add( _value);
        emit Transfer(msg.sender, _to, _value);
        return true; 
    }

    function transferFrom(address _from, address _to, uint256 _value) public returns (bool success) { 
        balances[_from] = balances[_from].sub(_value);
        balances[_to] = balances[_to].add(_value);
        allowances[_from][_to] = allowances[_from][_to].sub(_value);
        emit Transfer(_from, _to, _value);
        return true; 
    }

    function approve(address _spender, uint256 _value) public returns (bool success) { 
        allowances[msg.sender][_spender] = _value;
        emit Approval(msg.sender, _spender, _value);
        return true; 
    }

    function allowance(address _owner, address _spender) public view returns (uint256 remaining) { 
        return allowances[_owner][_spender]; 
    }
}
