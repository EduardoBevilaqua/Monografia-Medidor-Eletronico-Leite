<?php namespace App\Controllers;

use CodeIgniter\Config\View;

class Medidas extends BaseController{

    public function initController(\CodeIgniter\HTTP\RequestInterface $request, \CodeIgniter\HTTP\ResponseInterface $response, \Psr\Log\LoggerInterface $logger)
	{
		parent::initController($request, $response, $logger);
		$this->session = \Config\Services::session();
    }
    public function index(){
        
    }
    public function inserir(){
        if($this->request->getMethod() === 'post'){

            $dados = $this->request->getPost();
            if($dados['chave'] == "ABC123"){
                $animaisModel = new \App\Models\AnimaisModel();
                $animal = $animaisModel->where('nome_animal',$dados['nome_animal'])->find();
                if(count($animal) != 0){
                    foreach($animal as $animal){
                        $animal = $animal;
                    }
                    $medidasModel = new \App\Models\MedidasModel();
                    $medidasModel->set('data',date('Y-m-d H:i:s'));
                    $medidasModel->set('quantidade',$dados['quantidade']);
                    $medidasModel->set('Animais_id_Animal',$animal['id_animal']);
                    
                    if($medidasModel->insert()){
                        echo "Medida registrada com sucesso";
                    }
                    else{
                        echo "Erro ao registrar medida";
                    }
                }
                else{
                    echo "Animal não cadastrado";
                }
            }
            else{
                echo "Chave incorreta";
            }
        }
    }
    public function obterQuantidadeMensal(){
        if(isset($_SESSION['Logado'])){

            $medidasModel = new \App\Models\MedidasModel();
            $arrayDados = array();
            for($i = 1; $i <= 12; $i++){
                $cont = 0;
                $medidas = $medidasModel->where('data >=',"2021-$i-01")->where('data <=',"2021-$i-31")->find();
                foreach($medidas as $valor){
                    $cont = ($valor['quantidade']) + $cont;
                }
                $array = (object) array("medida" => $cont);   
                array_push($arrayDados, $array);  
            } 
            $myJSON  = json_encode($arrayDados);
            //print_r($arrayDados);
            echo $myJSON;
        }
    }
    public function obterQuantidadeDiaria(){
        if(isset($_SESSION['Logado'])){

            $medidasModel = new \App\Models\MedidasModel();
            $arrayDados = array();
            for($i = 0; $i <= 30; $i++){
                $cont = 0;
                
                $data = strtotime(date('Y-m-d'));
                $temp = strtotime("-$i day", $data);
                $dataLimite = date('Y-m-d', $temp);
                if($_SESSION['AnimalPainel'] == "Todas"){
                    $medidas = $medidasModel->where('data',$dataLimite)->find();
                }
                else{
                    $medidas = $medidasModel->where('data',$dataLimite)->where('Animais_id_Animal',$_SESSION['AnimalPainel'])->find();
                }
                foreach($medidas as $valor){
                    $cont = ($valor['quantidade']) + $cont;
                } 
                $array = (object) array("data" => (date('d/m', $temp)), "medida" => $cont);   
                array_push($arrayDados, $array);
            } 
            $myJSON  = json_encode($arrayDados);
            //print_r($arrayDados);
            echo $myJSON;
        }
    }

    public function obterQuantidadeAnimal(){
        if(isset($_SESSION['Logado'])){

            $medidasModel = new \App\Models\MedidasModel();
            $animaisModel = new \App\Models\AnimaisModel();
            $arrayDados = array();
            $dados = $animaisModel->find();
            foreach($dados as $valor){
                $cont = 0;
                $medidas = $medidasModel->where('Animais_id_Animal ',$valor['id_animal'])->find();
                foreach($medidas as $medidas){
                    $cont = ($medidas['quantidade']) + $cont;
                }
                
                $array = (object) array("nome_animal" => $valor['nome_animal'], "quantidadeTotal" => $cont);   
                array_push($arrayDados, $array);
            }
            $myJSON  = json_encode($arrayDados);
            //obterQuantidadeAnimal()
            echo $myJSON;
        }
    } 
}

?>
