<?php namespace App\Models;

use CodeIgniter\Model;

class UsuariosModel extends Model {
    
    protected $table = 'usuarios';
    protected $primaryKey = 'id_usuario';
    protected $allowedFields = ['nome_usuario','senha'];
    protected $returnType = 'object';

}
?>