// SPDX-License-Identifier: MIT

pragma solidity >0.8.0;

contract Test {
    int a = 300;
    int b = 12;
    int f = 47;

    int public stakingWallet = 10;

    function multiplyCalculator(int left, int right) internal pure returns(int) {
        int result = left * right;
        return result;
    }

    function finalize() external view returns(int) {
        int d = 23;
        return multiplyCalculator(d, d) - b;
    }

    function getSumOfDigits(int num) public pure returns(int) {
        if (num == 0) return 0;
        else return num % 10 + getSumOfDigits(num / 10);
    }

    function airDrop() public payable returns(int) {
        if (stakingWallet == 10)
            stakingWallet += 10;
        else stakingWallet += 1;

        return stakingWallet;
    }

    // function error() public pure returns(int) {
    //     return finalize();
    // }
}
