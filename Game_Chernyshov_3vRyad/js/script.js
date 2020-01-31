var fieldSize = 10;
var blockSize = 50;
var gamefieldArray;
var selectedCell = null;
var gamefield = document.getElementById("gamefield");
var colors = ["red", "blue", "green", "purple", "pink"];
var selectColor = "brown";
var matchColor = "yellow";
var gameStarted = false;
var score = 0;

var GameElem = function(i, j, cell) {
    this.xCoord = i;
    this.yCoord = j;
    this.cell = cell;
    this.toRemove = false;
    this.ball = null;

    this.removeBall = function () {
        this.cell.innerHTML = "";
        this.ball = null;
        this.toRemove = false;
        this.cell.style.backgroundColor = "lightgoldenrodyellow";
    }

    this.addBall = function (ball) {
        this.cell.append(ball);
        this.ball = ball;
    }

    this.isNextTo = function (cell) {
        return (Math.abs(this.xCoord - cell.xCoord) == 1 && cell.yCoord == this.yCoord)
            || (Math.abs(this.yCoord - cell.yCoord) == 1 && cell.xCoord == this.xCoord);
    }
}

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

var swap = function (cell1, cell2) {
    var temp = cell1.ball.style.backgroundColor;
    cell1.ball.style.backgroundColor = cell2.ball.style.backgroundColor;
    cell2.ball.style.backgroundColor = temp;
}

var selectCell = async function () {
    if (selectedCell != null) {
        if (selectedCell.elem.isNextTo(this.elem)) {
            this.style.backgroundColor = selectColor;
            swap(this.elem, selectedCell.elem);
            await sleep(500);
            if (check()) {
                if (this.style.backgroundColor == selectColor)
                    this.style.backgroundColor = gamefield.style.backgroundColor;
                if (selectedCell.style.backgroundColor == selectColor)
                    selectedCell.style.backgroundColor = gamefield.style.backgroundColor;
                updateField();
            } else {
                swap(this.elem, selectedCell.elem);
                this.style.backgroundColor = gamefield.style.backgroundColor;
                selectedCell.style.backgroundColor = gamefield.style.backgroundColor;
            }

            selectedCell = null;
            return;
        }
        else
            selectedCell.style.backgroundColor = gamefield.style.backgroundColor;
    }

    selectedCell = this;
    this.style.backgroundColor = selectColor;
}

var initialize = function () {
    var i, j;
    gamefield.style.height = (fieldSize * blockSize) + "px";
    gamefield.style.width = (fieldSize * blockSize) + "px";
    gamefield.classList.add("gamefield-disabled");
    gamefieldArray = new Array(fieldSize);

    var startButton = document.createElement("div");
    startButton.classList.add("startButton");
    startButton.innerHTML = "Играть";
    startButton.onclick = startGame;
    gamefield.append(startButton);
}

var startGame = function () {
    var i, j;
    this.style.display = "none";
    gamefield.classList.remove("gamefield-disabled");
    for (i = 0; i < fieldSize; i++) {
        var column = document.createElement("div");
        column.classList.add("column");
        column.style.height = (fieldSize * blockSize) + "px";
        column.style.width = blockSize + "px"; 
        gamefieldArray[i] = new Array(fieldSize);

        for (j = 0; j < fieldSize; j++) {
            var cell = document.createElement("div");
            cell.style.height = blockSize + "px";
            cell.style.width = blockSize + "px";
            cell.onclick = selectCell;
            cell.elem = new GameElem(i, j, cell);
            gamefieldArray[i][j] = cell.elem;
            column.append(cell);
        }

        gamefield.append(column);
    }

    updateField();
    gameStarted = true;
    score = 0;
    document.getElementById("score").innerHTML = score;
}

var updateField = async function () {
    var increase = 0;
    var comboCounter = 0;
    while (check()) {
        if (gameStarted) {
            comboCounter++;
            if (comboCounter > 1)
                document.getElementById("comboCounter").innerHTML = "Комбо: x" + comboCounter;

            await sleep(500);
        }
            
        var i;
        for (i = 0; i < fieldSize; i++)
            increase += updateColumn(i);

        if (gameStarted) {
            score += increase * increase;
            document.getElementById("score").innerHTML = score;
        }   
    }

    document.getElementById("comboCounter").innerHTML = "";
}

var updateColumn = function (i) {
    var j;
    for (j = fieldSize - 1; j >= 0; j--)
        if (gamefieldArray[i][j].toRemove)
            gamefieldArray[i][j].removeBall();

    var balls = [];
    for (j = fieldSize - 1; j >= 0; j--)
        if (gamefieldArray[i][j].cell.innerHTML != "")
            balls.push(gamefieldArray[i][j].ball);

    var counter = 0;
    for (j = balls.length; j < fieldSize; j++) {
        counter++;
        balls.push(generateBall(gamefieldArray[i][j].cell));
    } 

    balls.reverse();
    for (j = 0; j < fieldSize; j++) {
        gamefieldArray[i][j].cell.innerHTML = "";
        gamefieldArray[i][j].addBall(balls[j]);
    }

    return counter;
}

var check = function () {
    var i, j;
    var match = false;
    for (i = 0; i < fieldSize; i++)
        for (j = 0; j < fieldSize; j++)
            if (checkMatch(i, j, "Vertical") || checkMatch(i, j, "Horizontal") || checkMatch(i, j, "DiagonalUp") || checkMatch(i, j, "DiagonalDown"))
                match = true;

    return match;
}

var checkMatch = function (x, y, direction) {
    if (gamefieldArray[x][y].ball == null)
        return true;
    var color = gamefieldArray[x][y].ball.style.backgroundColor;
    if (direction == "Vertical") {
        var counter = 1;
        while (y + counter < fieldSize && gamefieldArray[x][y + counter].ball.style.backgroundColor == color)
            counter++;
        if (counter > 2) {
            var j;
            for (j = y; j < y + counter; j++) {
                gamefieldArray[x][j].cell.style.backgroundColor = matchColor;
                gamefieldArray[x][j].toRemove = true;
            }

            return true;
        } else return false;
    } else if (direction == "Horizontal") {
        var counter = 1;
        while (x + counter < fieldSize && gamefieldArray[x + counter][y].ball.style.backgroundColor == color)
            counter++;
        if (counter > 2) {
            var i;
            for (i = x; i < x + counter; i++) {
                gamefieldArray[i][y].cell.style.backgroundColor = matchColor;
                gamefieldArray[i][y].toRemove = true;
            } 

            return true;
        } else return false;
    } else if (direction == "DiagonalUp") {
        var counter = 1;
        while (x + counter < fieldSize && y - counter >= 0 && gamefieldArray[x + counter][y - counter].ball.style.backgroundColor == color)
            counter++;
        if (counter > 2) {
            var i;
            for (i = x; i < x + counter; i++) {
                gamefieldArray[i][y - i + x].cell.style.backgroundColor = matchColor;
                gamefieldArray[i][y - i + x].toRemove = true;
            }

            return true;
        } else return false;
    } else if (direction == "DiagonalDown") {
        var counter = 1;
        while (x + counter < fieldSize && y + counter < fieldSize && gamefieldArray[x + counter][y + counter].ball.style.backgroundColor == color)
            counter++;
        if (counter > 2) {
            var i;
            for (i = x; i < x + counter; i++) {
                gamefieldArray[i][y - x + i].cell.style.backgroundColor = matchColor;
                gamefieldArray[i][y - x + i].toRemove = true;
            }

            return true;
        } else return false;
    } else return false;
}

var generateBall = function () {
    var ball = document.createElement("div");
    ball.classList.add("ball");
    ball.style.width = blockSize + "px";
    ball.style.height = blockSize + "px";
    ball.style.backgroundColor = colors[Math.floor(Math.random() * colors.length)];
    return ball;
}

initialize();