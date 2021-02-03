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
    //alert("The form was submitted");
    var xhr = new XMLHttpRequest();
    // xhr.onload = function () {
    //     // do something to response
    //     console.log(this.responseText);
    // };
    // xhr.onreadystatechange = function() {
    //     if(this.readyState == 4 && this.status == 200){
    //         var myArr = JSON.parse(this.responseText);
    //         parseDtbInfo(myArr);
    //         console.log(myArr.host);
    //         document.getElementById("test").innerHTML = this.responseText;
    //     }
    // }
    xhr.open('POST', '/cfgdatabase', false);
    var a = "host=" + document.getElementById("host").value;
    a += "&port=" + document.getElementById("port").value;
    a += "&database=" + document.getElementById("database").value;
    a += "&user=" + document.getElementById("user").value;
    a += "&pwd=" + document.getElementById("pwd").value;
    xhr.send(a);
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
    var xhr = new XMLHttpRequest();
    xhr.open('POST', '/setwifi.asp', false);
    xhr.onload = function () {
        // do something to response
        console.log(this.responseText);
    };
    var a = "ssid=" + document.getElementById("ssid").value +"&pwd=" + document.getElementById("pwd").value;
    xhr.send(a);
    //alert("The form was submitted");
}