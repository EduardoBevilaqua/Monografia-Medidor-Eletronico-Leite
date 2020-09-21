<?php namespace App\Models;

use CodeIgniter\Model;

class MedidasModel extends Model {
    
    protected $table = 'medidas';
    protected $primaryKey = 'id_Medida';
    protected $allowedFields = ['data','quantidade','Animais_id_Animal'];
    protected $returnType = 'object';

}
?>