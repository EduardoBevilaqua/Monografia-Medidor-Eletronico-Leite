<?php namespace App\Models;

use CodeIgniter\Model;

class MedidasModel extends Model {
    
    protected $table = 'Medidas';
    protected $primaryKey = 'id_Medida';
    protected $allowedFields = ['data','quantidade','Animais_id_Animal'];
    protected $returnType = 'array';

    protected $afterFind = ['protecaoXSS'];

    protected function protecaoXSS($data){
        $data = esc($data);
        return $data;
    }
}
?>