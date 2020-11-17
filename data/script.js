(function () {
  let ledState;

  function setLEDButtonState(){
    const { red, yellow, green } = ledState;

    const redButton = document.getElementById("redButton");
    Number(red)
      ? redButton.classList.add("on")
      : redButton.classList.remove("on");

    const yellowButton = document.getElementById("yellowButton");
    Number(yellow)
      ? yellowButton.classList.add("on")
      : yellowButton.classList.remove("on");

    const greenButton = document.getElementById("greenButton");
    Number(green)
      ? greenButton.classList.add("on")
      : greenButton.classList.remove("on");
  }

  const connection = new WebSocket("ws://" + location.hostname + ":8081/", [
    "arduino",
  ]);
  connection.onopen = function () {
    connection.send("Websocket Connect " + new Date());
  };

  connection.onerror = function (error) {
    console.log("WebSocket error ", error);
  };

  connection.onmessage = function (e) {
    console.log("Websocket onMessage: ", e.data);
    if (e.data !== "Connected") {
      const {
        date,
        temperature,
        humidity,
        motion,
        leds
      } = JSON.parse(e.data);
      
      const options = { weekday: 'long', year: 'numeric', month: 'long', day: 'numeric', hour:'numeric', minute:'numeric', second:'numeric'};
      const currentDate = new Date(Date(date));

      ledState = leds;

      switch (document.title) {
        case "Temperature":
          if (!isNaN(Number(temperature))) {
            document.getElementById("temperature").innerHTML = Number(
              temperature
            ).toFixed(2);
            document.getElementById("humidity").innerHTML = Number(
              humidity
            ).toFixed(2);
          }
          document.getElementById("updateTime").innerHTML = currentDate.toLocaleDateString('en-US',options);
          break;

        case "Home":
          document.getElementById("updateTime").innerHTML = currentDate.toLocaleDateString('en-US',options);
          const motionEl = document.getElementById("motion");
          motionEl.innerHTML = motion? "YES" : "NO";
          motion
            ? motionEl.classList.add("detected")
            : motionEl.classList.remove("detected");
    
          break;

        case "LEDs":
          setLEDButtonState();
          break;

        default:
          break;
      }
    }
  };

  connection.onclose = function () {
    console.log("WebSocket connection closed");
  };

  function handleButtonClick(name){
    ledState[name] = ledState[name] ? 0 : 1;
    setLEDButtonState();
    connection.send(JSON.stringify(ledState));
  }

  const callback = function(){
    if(document.title == "LEDs") {
      document.getElementById("redButton").addEventListener("click",()=>(handleButtonClick("red")));
      document.getElementById("yellowButton").addEventListener("click",()=>(handleButtonClick("yellow")));
      document.getElementById("greenButton").addEventListener("click",()=>(handleButtonClick("green")));
    }
  };
  
  if (
      document.readyState === "complete" ||
      (document.readyState !== "loading" && !document.documentElement.doScroll)
  ) {
    callback();
  } else {
    document.addEventListener("DOMContentLoaded", callback);
  }
})();
