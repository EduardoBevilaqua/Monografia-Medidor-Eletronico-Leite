<?php namespace App\Models;

use CodeIgniter\Model;

class AnimaisModel extends Model {
    
    protected $table = 'Animais'; // Nome da tabela
    protected $primaryKey = 'id_animal'; // Chave primaria da tabela
    protected $allowedFields = ['nome_animal','raca','dataNascimento']; // Demais campos da tabela
    protected $returnType = 'array'; // Formato de retorno de dados, pode ser Array ou object

    protected $afterFind = ['protecaoXSS']; // chama a função protecaoXSS apos realizar uma busca

    protected function protecaoXSS($data){
        $data = esc($data);
        return $data;
    }
}
?>