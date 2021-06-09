<?php namespace App\Controllers;

use CodeIgniter\Config\View;

class Animais extends BaseController{

    public function initController(\CodeIgniter\HTTP\RequestInterface $request, \CodeIgniter\HTTP\ResponseInterface $response, \Psr\Log\LoggerInterface $logger)
	{
		parent::initController($request, $response, $logger);
		$this->session = \Config\Services::session();
    }
    public function index(){
        
        if(isset($_SESSION['Logado'])){
            $data['titulo'] = 'Animais';
            $data['msg'] = $this->session->getFlashdata('msg');
    
            $medidasModel = new \App\Models\MedidasModel();
            $animaisModel = new \App\Models\AnimaisModel();
            $dados = $animaisModel->find();
          
            if(count($dados)>0){
                foreach($dados as $dados){
                    $cont = 0;
                    $medidas = $medidasModel->where('Animais_id_Animal ',$dados['id_animal'])->find();
                    $qtdMedidas = count($medidas);
                    if($qtdMedidas == 0){
                        $qtdMedidas = 1;
                    }
                    
                    foreach($medidas as $medidas){
                        $cont = ($medidas['quantidade']) + $cont;
                    }
                    $dados['quantidadeTotal'] = $cont;
                    $dados['quantidadeOrdenha'] = $cont / $qtdMedidas;
                    $arrayDados[$dados['id_animal']] = $dados;
                }
            
                $data['animais'] = $arrayDados;
                
            }
            else{
                $data['animais'] = $dados;
            }
            echo view('animais', $data);
        }
        else{
            return redirect()->to(base_url('public/Login'));
        }
       
    }

    /*public function listaAnimais(){
        $arrayDados = array();
        $animaisModel = new \App\Models\AnimaisModel();
        $dados = $animaisModel->find();
        foreach($dados as $dados){
            array_push($arrayDados, $dados->nome_animal); 
        }
        
        $myJSON  = json_encode($arrayDados);
        
        echo $myJSON;
    }*/

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

    public function inserir(){
        if(isset($_SESSION['Logado'])){
            $animaisModel = new \App\Models\AnimaisModel();
            $data['titulo'] = 'Inserir Animal';
            $data['acao'] = 'Cadastrar';
            $data['msg'] = '';

            if($this->request->getMethod() === 'post'){

                $dadoscliente = $this->request->getPost();
                    
                if($animaisModel->insert($dadoscliente)){
                    $this->session->setFlashdata('msg', 'Animal cadastrado com sucesso!'); 
                    return redirect()->to(base_url('public/Animais'));
                }
                else{
                    $data['msg'] = 'Erro ao cadastrar Animal';
                    $data['erros'] =$animaisModel->errors();
                }      
            }
            echo view('animais_formulario', $data);
        }
        else{
            return redirect()->to(base_url('public/Login'));
        }
    }

    public function editar($id){
        if(isset($_SESSION['Logado'])){
            $data['titulo'] = 'Editar Cliente';
            $data['acao'] = 'Editar';
            $data['msg'] = '';
            $data['erros'] = '';
    
            $animaisModel = new \App\Models\AnimaisModel();
            $animal = $animaisModel->find($id);
    
            if(is_null($animal)){
                $this->session->setFlashdata('msg', 'Animal não encontrado!');
                return redirect()->to(base_url('public/Animais'));
            }
            else if($this->request->getMethod() === 'post'){
                $dadosAnimal = $this->request->getPost();
                if($animaisModel->update($id, $dadosAnimal)){
                    $this->session->setFlashdata('msg', 'Animal editado com sucesso!');
                    return redirect()->to(base_url('public/Animais'));
                }
                else{
                    $data['msg'] = 'Erro ao editar Animal!';
                }   
            }    
            $data['animal'] = $animal;
            echo view('animais_formulario', $data);
        }
        else{
            return redirect()->to(base_url('public/Login'));
        }
    }

    public function excluir($id = null){
        if(isset($_SESSION['Logado'])){
            $animaisModel = new \App\Models\AnimaisModel();
            $animal = $animaisModel->find($id);
    
            if(is_null($animal)){
                $this->session->setFlashdata('msg', 'Animal não encontrado!');
                return redirect()->to(base_url('public/Animais'));
            }
            if($animaisModel->delete($id)){
                $this->session->setFlashdata('msg', 'Animal excluido com sucesso');
            }
            else{
                $this->session->setFlashdata('msg', 'Erro ao excluir Animal');
            }
            return redirect()->to(base_url('public/Animais'));
        }
        else{
            return redirect()->to(base_url('public/Login'));
        }
    }
}


?>
