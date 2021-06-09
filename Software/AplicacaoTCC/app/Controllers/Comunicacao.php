<?php namespace App\Controllers;

use CodeIgniter\Config\View;

class Comunicacao extends BaseController{

    public function initController(\CodeIgniter\HTTP\RequestInterface $request, \CodeIgniter\HTTP\ResponseInterface $response, \Psr\Log\LoggerInterface $logger)
	{
		parent::initController($request, $response, $logger);
		$this->session = \Config\Services::session();
    }

    public function listaAnimais(){
        if($this->request->getMethod() === 'post'){

            $dados = $this->request->getPost();
            if($dados['chave'] == "ABC123"){
                $arrayDados = array();
                    
                $animaisModel = new \App\Models\AnimaisModel();
                
                $Animais = $animaisModel->find();
                //print_r($Animais);
                $i=1;
                foreach($Animais as $animais){
                    $arrayDados['vaca'.$i] =  $animais['nome_animal']; 
                    //$array = array("vaca" => $animais['nome_animal']);   
                    //array_push($arrayDados, $array);
                    $i++;
                }
                if(isset($arrayDados)){
                    //print_r($arrayDados);
                    $myJSON  = json_encode($arrayDados);
                    echo $myJSON;
                }
            }
            else{
                echo "Chave Incorreta";
            }
        }
    }


}


?>
