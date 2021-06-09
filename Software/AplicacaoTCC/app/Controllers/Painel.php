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
            $animaisModel = new \App\Models\AnimaisModel();
            $arrayAnimais = [];
            
            $listaAnimais = $animaisModel->find();    
            foreach ($listaAnimais as $animais){
                $arrayAnimais[$animais['id_animal']] = $animais['nome_animal'];
            }
            
            if($this->request->getMethod() === 'post'){
                $idAnimal = $this->request->getPost();
                if($idAnimal['idAnimal'] == "Todas"){
                    $_SESSION['AnimalPainel'] = $idAnimal['idAnimal'];
                    $_SESSION['nomeAnimalPainel'] = "Todas";
                }
                else{
                    $_SESSION['AnimalPainel'] = $idAnimal['idAnimal'];
                    $vaca = $animaisModel->find($idAnimal['idAnimal']); 
                    $_SESSION['nomeAnimalPainel'] = $vaca['nome_animal'];
                    
                }   
            }
            
            $data['listaAnimais'] = $arrayAnimais;
            echo view('painel', $data);
        }
        else{
            return redirect()->to(base_url('public/Login'));
        }
    }
}


?>
