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

  <title><?php echo $titulo?></title>
</head> 
<body>
  <?php include('navbar.php') ?>
  <br><br>
  <div class="container">
    <div class = "d-flex justify-content-center" >
        <form class="text-center  pt-3 px-5" action="#!">
            <div class="row " >
                <div class="col">
                    <div class="input-group ">
                        <div class="input-group-prepend">
                            <div class="input-group-text">@</div>
                        </div>
                        <input style="height: 38px;" type="text" class="form-control" id="inlineFormInputGroupUsername2" placeholder="Pesquisar Animal">
                    </div>
                </div> 
                <div class="col">   
                    <button class="btn btn-primary btn-block  mb-2 " style="height: 38px; " type="submit">Pesquisar</button>
                </div>
            </div>
        </form>    
    </div>
    <br>
    <div class="card">
        <h3 class="card-header text-center font-weight-bold text-uppercase py-4">Animais</h3>
        <div class="card-body">
        <span class="table-add float-right mb-3 mr-2"><a href="<?php echo base_url('public/Animais')?>" class="text-success"><i class="fas fa-redo cyan-text fa-2x"></i></a></span>
        <span class="table-add float-right mb-3 mr-2"><a href="<?php echo base_url('public/Animais/inserir')?>" class="text-success"><i class="fas fa-plus fa-2x"></i></a></span>
        <strong><?php echo $msg?></strong>
            <table class="table table-striped text-center">
                <thead class="blue lighten-1"> 
                    <tr>
                    <th scope="col">Cod</th>
                    <th scope="col">Nome</th>
                    <th scope="col">Raça</th>
                    <th scope="col">Data Nascimento</th>
                    <th scope="col">Qtd Media por Ordenha</th>
                    <th scope="col">Quantidade Total</th>
                    <th scope="col">Ações</th>
                    </tr>
                </thead>
                <tbody>
                    <?php foreach ($animais as $animais) : ?> 
                        <tr>
                        <th scope="row"><?php echo $animais->id_Animal?></th>
                        <td><?php echo $animais->nome_animal?></td>
                        <td><?php echo $animais->raca?></td>
                        <td><?php   $data = strtotime($animais->dataNascimento);
                                    echo date('d/m/Y', $data); ?></td>
                        <td><?php echo $animais->quantidadeOrdenha?> Litros</td>
                        <td><?php echo $animais->quantidadeTotal?> Litros</td>
                        <td class="pt-3-half" style="max-width: 90px"><a href="<?php echo base_url('public/Animais/editar/'.$animais->id_Animal)?>">
                                          <i class="fas fa-user-edit fa-1x cyan-text mx-1 my-1"></i>
                                        </a>
                                        <a href="<?php echo base_url('public/Animais/excluir/'.$animais->id_Animal)?>">
                                          <i class="fas fa-trash fa-1x red-text"></i>
                                        </a>  
                        </td>
                        </tr>
                    <?php endforeach?>
                </tbody>
            </table>
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


</body>  
</html>
