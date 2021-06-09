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
      
        <form class="text-center border border-light pt-3 px-5" style="width: 500px;" method="post">

            <p class="h4 mb-4">Cadastrar Animal</p>

            <div class="input-group mb-2 mr-sm-2">
                <div class="input-group-prepend">
                    <div class="input-group-text">@</div>
                </div>
                <input type="text" name="nome_animal" value="<?php echo (isset($animal) ? $animal['nome_animal'] : '') ?>" class="form-control py-0" id="inlineFormInputGroupUsername2" placeholder="Nome">
            </div>

            <div class="input-group mb-2 mr-sm-2">
                <div class="input-group-prepend">
                    <div class="input-group-text">@</div>
                </div>
                <input type="text" name="raca" value="<?php echo (isset($animal) ? $animal['raca'] : '') ?>" class="form-control py-0" id="inlineFormInputGroupUsername2" placeholder="Raça">
            </div>

            <div class="input-group mb-2 mr-sm-2">
                <div class="input-group-prepend">
                    <div class="input-group-text">@</div>
                </div>
                <input type="date" name="dataNascimento" value="<?php echo (isset($animal) ? $animal['dataNascimento'] : '') ?>" class="form-control py-0" id="inlineFormInputGroupUsername2" placeholder="Data Nascimento">
            </div>
            
            <button class="btn btn-primary btn-block  my-4" type="submit"><?php echo $acao ?></button>
        </form>     
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


</body>  
</html>
