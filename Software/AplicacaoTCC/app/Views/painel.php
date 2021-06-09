<!doctype html>
<html lang="pt-br">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
  <meta http-equiv="x-ua-compatible" content="ie=edge">

  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.8.2/css/all.css">
  <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Roboto:300,400,500,700&display=swap">
  <link href="https://cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/4.5.0/css/bootstrap.min.css" rel="stylesheet">
  <link href="https://cdnjs.cloudflare.com/ajax/libs/mdbootstrap/4.19.1/css/mdb.min.css" rel="stylesheet">

  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.9.3/Chart.css" integrity="sha512-SUJFImtiT87gVCOXl3aGC00zfDl6ggYAw5+oheJvRJ8KBXZrr/TMISSdVJ5bBarbQDRC2pR5Kto3xTR0kpZInA==" crossorigin="anonymous" />

  <link href="<?php echo base_url('public/css/style.css')?>" type="text/css" rel="stylesheet">
  <title><?php echo $titulo?></title>
</head> 
<body>
  <?php include('navbar.php') ?>
  <br><br>
  <div class="container">
    <div class = "d-flex justify-content-center" >
      <div class="row">
        <div class="card">
          <h3 class="card-header text-center font-weight-bold text-uppercase py-4">Produção Diaria <?php echo $_SESSION['nomeAnimalPainel']?> </h3>
          <div class="card-body" >
            <div class="container" style="max-width: 400px;">
              <form class="text-center mb-1" method="post" >
              <div class="row">
                  <div class="col px-1">
                    <select name="idAnimal" style="height: 40px;" class="browser-default custom-select mb-4" >
                        <option selected>Todas</option>
                        <?php foreach ($listaAnimais as $idAnimal => $nome_animal): ?>
                            <?php echo "<option value=\"$idAnimal\" >$nome_animal</option>"; ?>
                        <?php endforeach; ?>
                    </select>
                  </div>
                  <div class="col px-1">
                    <button class="btn btn-info btn-block mb-4" style="height: 40px;" type="submit">Selecionar</button>
                  </div>
                  </div>
              </form>
            </div>
            <canvas style="width: 600px;" id="producaoDiaria"></canvas>
          </div>
        </div>
      </div>
    </div>
    
    <br>
    <div class="row">
      <div class="col">
        <div class="card">
          <h3  class="card-header text-center font-weight-bold text-uppercase py-4">Produção por Vaca</h3>
          <div class="card-body">
            <canvas id="producaoPorVaca"></canvas>
          </div>
        </div>
      </div>
      <div class="col">
        <div class="card">
          <h3  class="card-header text-center font-weight-bold text-uppercase py-4">Produção Mensal</h3>
          <div class="card-body">
            <canvas id="producaoMensal"></canvas>
          </div>
        </div>
      </div>
    </div>    
  </div>
  <br><br><br>
  <?php include('rodape.php') ?>



<script src="https://cdn.jsdelivr.net/npm/chart.js@2.8.0"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.9.3/Chart.js" integrity="sha512-QEiC894KVkN9Tsoi6+mKf8HaCLJvyA6QIRzY5KrfINXYuP9NxdIkRQhGq3BZi0J4I7V5SidGM3XUQ5wFiMDuWg==" crossorigin="anonymous"></script>
<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.4/umd/popper.min.js"></script>
<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/4.5.0/js/bootstrap.min.js"></script>
<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/mdbootstrap/4.19.1/js/mdb.min.js"></script>

<script>
  function graficoDiario(nome, qtd){

    var ctx = document.getElementById('producaoDiaria').getContext('2d');
    var chart = new Chart(ctx, {
        // The type of chart we want to create
        type: 'line',

        // The data for our dataset
        data: {
            labels: nome,
            datasets: [{
                label: 'Quantidade em Litros',
                backgroundColor: 'rgba(0, 0, 0, 0.0)',
                borderColor: 'rgb(0, 100, 200)',
                data: qtd
            }]
        },

        // Configuration options go here
        options: {}
    });
  }

  function graficoMensal(qtd){

    var ctx = document.getElementById('producaoMensal').getContext('2d');
    var chart = new Chart(ctx, {
        // The type of chart we want to create
        type: 'bar',

        // The data for our dataset
        data: {
            labels: ['Janeiro', 'Fevereiro', 'Março', 'Abril', 'maio', 'Junho', 'Julho', 'Agosto','Setembro','Outubro', 'Novembro', 'Dezembro'],
            datasets: [{
                label: 'Quantidade em Litros',
                backgroundColor: 'rgb(0, 150, 255)',
                borderColor: 'rgb(0, 150, 255)',
                data: qtd
            }]
        },

        // Configuration options go here
        options: {}
    });
  }

  function graficoAnimal(nome, qtd){

    var ctx = document.getElementById('producaoPorVaca').getContext('2d');
    var chart = new Chart(ctx, {
        // The type of chart we want to create
        type: 'doughnut',

        // The data for our dataset
        data: {
            labels: nome,
            datasets: [{
                label: 'Quantidade em Litros',
                backgroundColor: ['rgb(0, 150, 255)','rgb(255, 50, 0)','rgb(150, 255, 0)'],
                borderColor: 'rgb(255, 255, 255)',
                data: qtd
            }]
        },

        // Configuration options go here
        options: {}
    });
  }
  $('document').ready(function(){
    $.ajax({
        type: "POST", 
        url: 'http://localhost/AplicacaoTCC/public/Medidas/obterQuantidadeAnimal',
        timeout: 3000,
        datatype: 'JSON',
        contentType: "application/json; charset=utf-8",
        cache: false,
        success: function(myJSON) {
          var nomeArray = [];
          var qtdArray = [];
          data = JSON.parse(myJSON);
          for(var i=0; data.length>i;i++){
            nomeArray.push(data[i].nome_animal);
            qtdArray.push(data[i].quantidadeTotal)
          }   
          graficoAnimal(nomeArray, qtdArray);
        },
      });

      $.ajax({
        type: "POST", 
        url: 'http://localhost/AplicacaoTCC/public/Medidas/obterQuantidadeDiaria',
        timeout: 3000,
        datatype: 'JSON',
        contentType: "application/json; charset=utf-8",
        cache: false,
        success: function(myJSON) {
          var nomeArray = [];
          var qtdArray = [];
          data = JSON.parse(myJSON); 
          for(var i=0; data.length>i;i++){  
            nomeArray.push(data[i].data);
            qtdArray.push(data[i].medida)
          }   
          nomeArray.reverse(); 
          qtdArray.reverse(); 
          graficoDiario(nomeArray, qtdArray);
        },
      });

      $.ajax({
        type: "POST", 
        url: 'http://localhost/AplicacaoTCC/public/Medidas/obterQuantidadeMensal',
        timeout: 3000,
        datatype: 'JSON',
        contentType: "application/json; charset=utf-8",
        cache: false,
        success: function(myJSON) {
          var qtdArray = [];
          data = JSON.parse(myJSON); 
          for(var i=0; data.length>i;i++){  
            qtdArray.push(data[i].medida)
          }   
          graficoMensal(qtdArray);
        },
      });   
  })
</script>

</body>  
</html>
