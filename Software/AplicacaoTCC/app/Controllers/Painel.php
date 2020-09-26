<?php namespace App\Controllers;

use CodeIgniter\Config\View;

class Painel extends BaseController{

    public function initController(\CodeIgniter\HTTP\RequestInterface $request, \CodeIgniter\HTTP\ResponseInterface $response, \Psr\Log\LoggerInterface $logger)
	{
		parent::initController($request, $response, $logger);
		$this->session = \Config\Services::session();
    }
    public function index(){
        $data['titulo'] = 'Painel';
        if(isset($_SESSION['Logado'])){
            echo view('painel', $data);
        }
        else{
            return redirect()->to(base_url('public/Login'));
        }
    }
}


?>
