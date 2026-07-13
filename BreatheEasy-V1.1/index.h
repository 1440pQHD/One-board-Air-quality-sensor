const char webpage[] = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  

  <link rel="preconnect" href="https://fonts.googleapis.com">
  <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
  <link href="https://fonts.googleapis.com/css2?family=Audiowide&display=swap" rel="stylesheet">

  <style>
    body {
      margin: 0;
      background: #2c5ead;
      font-family: 'Audiowide', sans-serif;
      display: flex;
      justify-content: center;
      align-items: center;
      height: 100vh;
    }
    .container {
      width: 300px;
      background: #C4E2F5;
      border-radius: 18px;
      padding: 30px;
      box-shadow: 0 12px 32px rgba(0,0,0,.09);
    }
    .status {
      padding: 6px 12px;
      border-radius: 999px;
      font-size: 0.85rem;
      background: #4647AE;
      color: #AACCD6;
      font-weight: 600;
      text-align: center;
      margin-bottom: 15px;
    }
    .logo {
      display: block;
      margin: auto;
      width: 100px;
      margin-bottom: 20px;
    }
    h1 {
      text-align: center;
      margin: 0;
      font-size: 32px;
      color: #112E81;
    }
    .subtitle {
      text-align: center;
      color: #112E81;
      margin-top: 10px;
      margin-bottom: 30px;
    }
    .card {
      background: #4BB8FA;
      border-radius: 15px;
      padding: 18px;
      margin-bottom: 15px;
    }
    .label {
      color: #112E81;
      font-size: 15px;
      margin-bottom: 5px;
    }
    .value {
      font-size: 24px;
      font-weight: bold;
      color: #ffffff;
    }
    .footer {
      text-align: center;
      color: #4647AE;
      margin-top: 20px;
      font-size: 13px;
    }
  </style>
</head>
<body>
  
  <div class="container">
    <img class="logo" src="https://i.ibb.co/352FNBKK/image.png" alt="Logo">
    <h1>BreatheEasy</h1>
    <div class="subtitle">ESP32 Data Dashboard</div>

    <div class="status" id="status">
      🟢 Service Nominal
    </div>

    <div class="card">
      <div class="label">Temperature</div>
      <div class="value" id="temperature">--</div>
    </div>

    <div class="card">
      <div class="label">Humidity</div>
      <div class="value" id="humidity">--</div>
    </div>

    <div class="card">
      <div class="label">MQ-3 Alcohol Sensor</div>
      <div class="value" id="mq3">Warming Up...</div>
      <div class="value" id="mqstatus">Starting...</div>
    </div>

    <div class="card">
      <div class="label">Latest Event</div>
      <div class="value" id="event">System Starting...</div>
    </div>

    <div class="footer">
      <div>Uptime: <span id="uptime">--</span></div>
      <div>Updated: <span id="updated">--</span></div>
    </div>
  </div>

<script>
    console.log("dashboard script loaded");
    let alarmPlaying = false;
    let audioContext = null;
    let alarmInterval = null;

    function startAlarm(){
      if(alarmPlaying) return;
      alarmPlaying = true;

      audioContext = new (window.AudioContext || window.webkitAudioContext)();

      alarmInterval = setInterval(() => {
        let oscillator = audioContext.createOscillator();
        let gainNode = audioContext.createGain();

        oscillator.type = "square";
        oscillator.frequency.value = 600;
        gainNode.gain.value = 0.1;

        oscillator.connect(gainNode);
        gainNode.connect(audioContext.destination);

        oscillator.start();
        setTimeout(() => {
          oscillator.stop();
        }, 200);
      }, 500);
    }

    function stopAlarm(){
      alarmPlaying = false;
      if(alarmInterval){
        clearInterval(alarmInterval);
        alarmInterval = null;
      }
      if(audioContext){
        audioContext.close();
        audioContext = null;
      }
    }

    async function updateDashboard(){
      try { // <-- Added the missing try block here
        const response = await fetch('/data');
        const data = await response.json();
        console.log("Updating dashboard...");

        document.getElementById('temperature').innerHTML = data.temperature + " °C";
        document.getElementById('humidity').innerHTML = data.humidity + " %";
        document.getElementById('uptime').innerHTML = data.uptime;
        document.getElementById('updated').innerHTML = data.time;
        document.getElementById('event').innerHTML = data.event;

        if(data.mqReady){
          document.getElementById('mq3').innerHTML = "ADC: " + data.mq;
          document.getElementById('mqstatus').innerHTML = "Sensor OK";
        } else {
          document.getElementById('mq3').innerHTML = "Warming Up";
          document.getElementById('mqstatus').innerHTML = data.remaining + "s Remaining";
        }

        const statusElem = document.getElementById("status");
        if(data.alarm){
          statusElem.innerHTML = "🚨 ALERT";
          statusElem.style.background = "#FF0000";
          statusElem.style.color = "#FFFFFF";
          startAlarm();
        } else {
          statusElem.innerHTML = "🟢 Normal";
          statusElem.style.background = "#00FF00";
          statusElem.style.color = "#112E81";
          stopAlarm();
        }
      } catch (err) {
        console.error("Error fetching dashboard data:", err);
      }
    }

    updateDashboard();
    setInterval(updateDashboard, 1000);
</script>
</body>
</html>
)rawliteral";