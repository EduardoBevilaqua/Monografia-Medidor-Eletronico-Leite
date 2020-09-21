<?php namespace App\Models;

use CodeIgniter\Model;

class AnimaisModel extends Model {
    
    protected $table = 'animais';
    protected $primaryKey = 'id_animal';
    protected $allowedFields = ['nome_animal','raca','dataNascimento'];
    protected $returnType = 'object';

}
?>