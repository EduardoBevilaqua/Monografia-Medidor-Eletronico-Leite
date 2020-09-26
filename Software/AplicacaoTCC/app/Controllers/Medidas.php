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
    public function inserir($chave,$nome_animal, $medida){
        if($chave == "ABC123"){
            $animaisModel = new \App\Models\AnimaisModel();
            $animal = $animaisModel->where('nome_animal',$nome_animal)->find();
            if(count($animal) != 0){
                foreach($animal as $animal){
                    $animal = $animal;
                }
                $medidasModel = new \App\Models\MedidasModel();
                $medidasModel->set('data',date('Y-m-d H:i:s'));
                $medidasModel->set('quantidade',$medida);
                $medidasModel->set('Animais_id_Animal',$animal->id_Animal);
                
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
    public function obterQuantidadeMensal(){
        $medidasModel = new \App\Models\MedidasModel();
        $arrayDados = array();
        for($i = 1; $i <= 12; $i++){
            $cont = 0;
            $medidas = $medidasModel->where('data >=',"2020-$i-01")->where('data <=',"2020-$i-31")->find();
            foreach($medidas as $valor){
                $cont = ($valor->quantidade) + $cont;
            }
            $array = (object) array("medida" => $cont);   
            array_push($arrayDados, $array);  
        } 
         $myJSON  = json_encode($arrayDados);
         //print_r($arrayDados);
         echo $myJSON;
    }
    public function obterQuantidadeDiaria(){
        $medidasModel = new \App\Models\MedidasModel();
        $arrayDados = array();
        for($i = 0; $i <= 30; $i++){
            $cont = 0;
            
            $data = strtotime(date('Y-m-d'));
            $temp = strtotime("-$i day", $data);
            $dataLimite = date('Y-m-d', $temp);
            $medidas = $medidasModel->where('data',$dataLimite)->find();
            foreach($medidas as $valor){
                $cont = ($valor->quantidade) + $cont;
            } 
            $array = (object) array("data" => (date('d/m', $temp)), "medida" => $cont);   
            array_push($arrayDados, $array);
        } 
         $myJSON  = json_encode($arrayDados);
         //print_r($arrayDados);
         echo $myJSON;
    }

    public function obterQuantidadeAnimal(){
        $medidasModel = new \App\Models\MedidasModel();
        $animaisModel = new \App\Models\AnimaisModel();
        $dados = $animaisModel->find();
        foreach($dados as $valor){
            $cont = 0;
            $medidas = $medidasModel->where('Animais_id_Animal ',$valor->id_Animal)->find();
            foreach($medidas as $medidas){
                $cont = ($medidas->quantidade) + $cont;
            }
            $valor->quantidadeTotal = $cont;
        }
         $myJSON  = json_encode($dados);
         //print_r($dados);
         echo $myJSON;
    } 
}

?>
