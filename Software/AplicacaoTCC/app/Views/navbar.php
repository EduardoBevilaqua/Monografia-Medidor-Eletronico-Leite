<div class="container mt-1">
  <nav class="navbar navbar-expand-lg navbar-dark blue-gradient text-centers rounded-pill ">
    <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNav"
      aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
      <span class="navbar-toggler-icon"></span>
    </button>
    <div class="collapse navbar-collapse" id="navbarNav">

      <ul class="navbar-nav nav-flex-icons">
          <li class="nav-item dropdown" style="width: 53.56px;">
          </li>
      </ul>

      <ul class="navbar-nav mx-auto">
        <li class="nav-item mr-1">
          <a class="nav-link" href="<?php echo base_url('Painel')?>">Painel</a>
        </li>
        <li class="nav-item ml-1">
          <a class="nav-link" href="<?php echo base_url('Animais')?>">Animais</a>
        </li>
      </ul>

      <ul class="navbar-nav nav-flex-icons">
        <li class="nav-item dropdown">
            <a class="nav-link dropdown-toggle" id="navbarDropdownMenuLink-333" data-toggle="dropdown"
              aria-haspopup="true" aria-expanded="false">
              <i class="fas fa-user"></i>
            </a>
            <div class="dropdown-menu dropdown-menu-right dropdown-default"
              aria-labelledby="navbarDropdownMenuLink-333">
              <!--<a class="dropdown-item" href="#"><i class="fas fa-user"></i> Minha Conta</a>-->
              <a class="dropdown-item" href="<?php echo base_url('Login/Desconectar')?>"><i class="fas fa-sign-out-alt"></i> Sair</a>
            </div>
          </li>
        </ul>
    </div>
  </nav>
</div>