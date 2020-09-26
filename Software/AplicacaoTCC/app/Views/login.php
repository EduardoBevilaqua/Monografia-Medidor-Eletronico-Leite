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

  <title><?php echo $titulo?></title>
</head> 
<body >
    
    <div class="container p-5" style="max-width: 450px">
        <form class="text-center border border-light p-5" method="post">
            <p class="h4 mb-4">Login</p>
            <input type="text" name="nome_usuario" class="form-control mb-4" placeholder="Usuario">
            <input type="password" name="senha" class="form-control mb-4" placeholder="Senha">
            <strong><?php echo $msg?></strong>
            <div class="d-flex justify-content-around">
                <div>
                    <a href="">Esqueceu a senha?</a>
                </div>
            </div>
            <button class="btn btn-info btn-block my-4" type="submit">Logar</button>

            <p>Não tem cadastro?
                <a href="<?php echo base_url('public/Login/cadastro')?>">Cadastre-se</a>
            </p>

        </form>
    </div>   
    <br><br><br> 
    <?php include('rodape.php') ?>


<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.4/umd/popper.min.js"></script>
<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/4.5.0/js/bootstrap.min.js"></script>
<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/mdbootstrap/4.19.1/js/mdb.min.js"></script>

</body>  
</html>