const cosino = document.getElementById("cosino");
const tastierino = document.getElementById("tastierino");

const commandMap = {
    "ArrowDown": "backward",
    "ArrowUp": "forward",
    "ArrowLeft": "left",
    "ArrowRight": "right",
    " ": "shoot"
}
const delay = 100;

const isActive = () => document.getElementById("active").checked;
const ipValue = () => document.getElementById("input").value;
const map = (key) => commandMap[key];
const url = (key) => { 
    const kn = map(key);
    if (typeof(kn) == "undefined") {
        throw new Error("invalid key");
    }
    return "http://" + ipValue() + ":8080/jolly/" + kn + "/"; 
}

const NONEKEY = 'none'
let activeKey = NONEKEY;
let activeError = false;
const onKeyDown = (evt) => activeKey = evt.key;
const onKeyUp = (evt) => activeKey = activeKey == evt.key ? NONEKEY : activeKey;

document.addEventListener("keydown", onKeyDown);
document.addEventListener("keyup", onKeyUp);

const arrUp     = document.getElementById("ArrowUp");
const arrDown   = document.getElementById("ArrowDown");
const arrLeft   = document.getElementById("ArrowLeft");
const arrRight  = document.getElementById("ArrowRight");
const arrSpace  = document.getElementById("space");

arrUp.addEventListener("touchstart",    () => onKeyDown({key: 'ArrowUp'}))
arrUp.addEventListener("mousedown",     () => onKeyDown({key: 'ArrowUp'}))
arrDown.addEventListener("touchstart",  () => onKeyDown({key: 'ArrowDown'}))
arrDown.addEventListener("mousedown",   () => onKeyDown({key: 'ArrowDown'}))
arrLeft.addEventListener("touchstart",  () => onKeyDown({key: 'ArrowLeft'}))
arrLeft.addEventListener("mousedown",   () => onKeyDown({key: 'ArrowLeft'}))
arrRight.addEventListener("touchstart", () => onKeyDown({key: 'ArrowRight'}))
arrRight.addEventListener("mousedown",  () => onKeyDown({key: 'ArrowRight'}))
arrSpace.addEventListener("touchstart", () => onKeyDown({key: ' '}))
arrSpace.addEventListener("mousedown",  () => onKeyDown({key: ' '}))

arrUp.addEventListener("touchend",    () => activeKey = NONEKEY );
arrUp.addEventListener("mouseup",     () => activeKey = NONEKEY );
arrDown.addEventListener("touchend",  () => activeKey = NONEKEY );
arrDown.addEventListener("mouseup",   () => activeKey = NONEKEY );
arrLeft.addEventListener("touchend",  () => activeKey = NONEKEY );
arrLeft.addEventListener("mouseup",   () => activeKey = NONEKEY );
arrRight.addEventListener("touchend", () => activeKey = NONEKEY );
arrRight.addEventListener("mouseup",  () => activeKey = NONEKEY );
arrSpace.addEventListener("touchend", () => activeKey = NONEKEY );
arrSpace.addEventListener("mouseup",  () => activeKey = NONEKEY );

let activeProc = setInterval(async() => {
    cosino.className = 'state_' + activeKey;
    tastierino.className = 'state_' + activeKey;
    if (activeError) cosino.classList.add("error_bad");
    if (activeKey == NONEKEY) return;
    let ur;
    try {
        ur = url(activeKey);
    } catch (e) {
        return;
    }

    if (isActive()) { 
        try {
            await fetch(ur) 
            activeError = false;
        } catch (e) {
            activeError = true;
        }
    }
    console.log(ur)
}, delay);
