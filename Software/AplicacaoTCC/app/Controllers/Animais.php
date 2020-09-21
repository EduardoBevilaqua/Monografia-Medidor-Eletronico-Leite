<?php namespace App\Controllers;

use CodeIgniter\Config\View;

class Animais extends BaseController{

    public function initController(\CodeIgniter\HTTP\RequestInterface $request, \CodeIgniter\HTTP\ResponseInterface $response, \Psr\Log\LoggerInterface $logger)
	{
		parent::initController($request, $response, $logger);
		$this->session = \Config\Services::session();
    }
    public function index(){
        
        $data['titulo'] = 'Animais';
        $data['msg'] = $this->session->getFlashdata('msg');

        $medidasModel = new \App\Models\MedidasModel();
        $animaisModel = new \App\Models\AnimaisModel();
        $dados = $animaisModel->find();

        foreach($dados as $dados){
            $cont = 0;
            $medidas = $medidasModel->where('Animais_id_Animal ',$dados->id_Animal)->find();
            $qtdMedidas = count($medidas);
            if($qtdMedidas == 0){
                $qtdMedidas = 1;
            }
            
            foreach($medidas as $medidas){
                $cont = ($medidas->quantidade) + $cont;
            }
            $dados->quantidadeTotal = $cont;
            $dados->quantidadeOrdenha = $cont / $qtdMedidas;
            $arrayDados[$dados->id_Animal] = $dados;
         }
        $data['animais'] = $arrayDados;
        echo view('animais', $data);
    }
    public function listaAnimais(){
        $arrayDados = array();
        $animaisModel = new \App\Models\AnimaisModel();
        $dados = $animaisModel->find();
        foreach($dados as $dados){
            array_push($arrayDados, $dados->nome_animal); 
        }
        $myJSON  = json_encode($arrayDados);
         //print_r($arrayDados);
         echo $myJSON;
    }
    public function inserir(){
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

    public function editar($id){

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

    public function excluir($id = null){
        
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
}


?>
