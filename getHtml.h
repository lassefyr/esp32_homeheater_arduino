#ifndef GETHTML_H
#define GETHTML_H

#include "pollPrice.h" // Ensure ReadPrice is known

class GetHTML {
private:
    ReadPrice* myP; // The pointer variable  
public:
    GetHTML(ReadPrice* priceObject); 
    void limUp();
    void limDown(); 
    String getTimeString();    
    String getPrices();
    String getBkCol();
    String getLimit();
    String processor(const String& var);
    //String getPage();
};
#endif

// --- HTML Parts stored in Flash Memory (PROGMEM) ---

const char index_html[] PROGMEM = R"raw(<!DOCTYPE html>
<html>
<head>
<title>Heater ON/OFF Cost Limit</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
.chart {
width: auto;
height: auto;
border: 1px solid black;
margin-top: 30px; /* <--- Add this line (adjust 30px to your liking) */
}
.pushable {
background: rgb(0, 102, 0);
border-radius: 12px;
border: none;
padding: 0;
cursor: pointer;
outline-offset: 4px;
}
.front {
    display: block;
    padding: 12px 42px;
    border-radius: 12px;
    font-size: 1.25rem;
    background: rgb(0, 153, 51);
    color: white;
    transform: translateY(-6px);
  }
.pushable:active .front {
    transform: translateY(-2px);
  }
</style>
</head>
<body>
<h1>Heater ON/OFF Cost Limit</h1>
<p>%TIME%</p>  <!-- Placeholder 1 -->
<button class="pushable" id="button1"><span class="front">Price Up</span></button>
<button class="pushable" id="button2"><span class="front">Price Down</span></button>
<script>
    var button1 = document.getElementById("button1");
    var button2 = document.getElementById("button2");
    button1.addEventListener("click", function() {
        fetch('/pup')
        .then(response => {
            console.log(response);
            location.reload(true);
        })
        .catch(error => { console.log("Error"); });
    });
    button2.addEventListener("click", function() {
        fetch('/pdown')
        .then(response => {
            console.log(response);
            location.reload(true);
        })
        .catch(error => { console.log(error); });
    });
</script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.5.0/Chart.min.js"></script>
<div class="chart">
    <canvas id="myChart"></canvas>
</div>
<script>
const ctx = document.getElementById('myChart').getContext('2d');
const data = {
    labels: ['00','01','02','03','04','05','06','07','08','09','10','11','12','13','14','15','16','17','18','19','20','21','22','23'],
    datasets: [
    {
    type: 'bar',
    label: 'Hour Price',
    data: [%PRICES%], <!-- Placeholder 2 -->
    backgroundColor: [%COLORS%], <!-- Placeholder 3 -->
    borderColor: 'rgba(75, 192, 192, 1)',
    borderWidth: 1
    },
    {
    type: 'line',
    label: 'Cost Limit',
    data: [%LIMITS%], <!-- Placeholder 4 -->
    fill: false,
    borderColor: 'rgba(192, 75, 192, 1)',
    borderWidth: 2
    }]};
const chart = new Chart(ctx, {
    type: 'bar',
    data: data,
    options: {
        animation: false,
        responsive: true,
        scales: {
            yAxes: [{
                ticks: {
                    beginAtZero: true     // force y-axis to start at 0
                }
            }]
        }
    }
});
</script>
</body>
</html>)raw";

