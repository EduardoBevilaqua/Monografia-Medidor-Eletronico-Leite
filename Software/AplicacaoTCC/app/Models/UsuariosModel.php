<?php namespace App\Models;

use CodeIgniter\Model;

class UsuariosModel extends Model {
    
    protected $table = 'Usuarios';
    protected $primaryKey = 'id_usuario';
    protected $allowedFields = ['nome_usuario','senha'];
    protected $returnType = 'array';

    protected $afterFind = ['protecaoXSS'];

    protected function protecaoXSS($data){
        $data = esc($data);
        return $data;
    }

}
?>