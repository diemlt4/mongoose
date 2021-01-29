function showPass() {
    var x = document.getElementById("pwd");
    if (x.type === "password") {
        x.type = "text";
    } else {
        x.type = "password";
    }
}
function myFunction() {
    alert("The form was submitted");
}
function loadDoc() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("demo").innerHTML = this.responseText;
        }
    };
    xhttp.open("GET", "/demourl", false);
    xhttp.send();
}
function confDtb() {
    alert("The form was submitted");
    var data = new FormData();
    data.append("users", document.getElementById("users").value);
    data.append('pwd', document.getElementById("pwd").value);

    var xhr = new XMLHttpRequest();
    xhr.open('POST', '/cfgdatabase', false);
    xhr.onload = function () {
        // do something to response
        console.log(this.responseText);
    };
    var a = "user=abfds";// + document.getElementById("user").value;
    xhr.send(data);
    //alert("The form was submitted");
}

function parseDtbInfo(arr) {
    var out = "";
    document.getElementById("host").value = arr.host;
    document.getElementById("port").value = arr.port;
    document.getElementById("database").value = arr.database;
    document.getElementById("user").value = arr.user;
    document.getElementById("pwd").value = arr.password;
}
function getCfg()
{
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if(this.readyState == 4 && this.status == 200){
            var myArr = JSON.parse(this.responseText);
            parseDtbInfo(myArr);
            console.log(myArr.host);
            document.getElementById("test").innerHTML = this.responseText;
        }
    }
    xhttp.open("GET", "/getcfg", false);
    xhttp.send();
}
function loadDoc() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("demo").innerHTML = this.responseText;
        }
    };
    xhttp.open("GET", "/demourl", false);
    xhttp.send();
}
function submitData() {
    var data = new FormData();
    data.append("ssid", document.getElementById("ssid").value);
    data.append('pwd', document.getElementById("pwd").value);

    var xhr = new XMLHttpRequest();
    xhr.open('POST', '/setwifi.asp', true);
    xhr.onload = function () {
        // do something to response
        console.log(this.responseText);
    };
    var a = "ssid=" + document.getElementById("ssid").value +"&pwd=" + document.getElementById("pwd").value;
    xhr.send(a);
    alert("The form was submitted");
}