<?php namespace App\Controllers;

use CodeIgniter\Config\View;

class Login extends BaseController
{

	public function initController(\CodeIgniter\HTTP\RequestInterface $request, \CodeIgniter\HTTP\ResponseInterface $response, \Psr\Log\LoggerInterface $logger)
	{
		parent::initController($request, $response, $logger);
		$this->session = \Config\Services::session();
	}
	
	public function index()
	{
		$data['titulo'] = 'Login';
		$data['msg'] = '';

		if($this->request->getMethod() === 'post'){
			$usuariosModel = new \App\Models\UsuariosModel();

			//$dados = $this->request->getPost();
			$nome_usuario = $this->request->getPost('nome_usuario');
			$senha = md5($this->request->getPost('senha'));
			$usuario = $usuariosModel->where('nome_usuario',$nome_usuario)->find();
			print_r($usuario);
			if(is_null($usuario)){
				$this->session->setFlashdata('msg', 'Credenciais invalidas!');
			}
			else{
				foreach($usuario as $user){
					if($user->senha == $senha){
						$_SESSION['Logado'] = TRUE;
						return redirect()->to(base_url('public'));
					}
					else{
						$this->session->setFlashdata('msg', 'Credenciais invalidas!');
					}
				}
			}
        }
        echo view('login', $data);
	}

	public function Desconectar(){
		session_destroy();
		return redirect()->to(base_url('public'));
	}

	public function cadastro(){
        $usuariosModel = new \App\Models\UsuariosModel();
        $data['titulo'] = 'Cadastrar Usuario';
        $data['acao'] = 'Cadastrar';
        $data['msg'] = '';

        if($this->request->getMethod() === 'post'){

			$dadoscliente = $this->request->getPost();
			$dadoscliente['senha'] = md5($dadoscliente['senha']);
		    
            if($usuariosModel->insert($dadoscliente)){
				$data['msg'] = 'Usuario cadastrado com sucesso!'; 
				//$this->session->setFlashdata('msg', 'Animal cadastrado com sucesso!'); 
                return redirect()->to(base_url('public/Login'));
            }
            else{
                $data['msg'] = 'Erro ao cadastrar Usuario';
                $data['erros'] =$usuariosModel->errors();
            }  
        }
        echo view('login_formulario', $data);
	}

	

	//--------------------------------------------------------------------

}
