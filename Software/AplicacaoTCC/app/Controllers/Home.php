<?php namespace App\Controllers;

class Home extends BaseController
{
	public function index()
	{
		$data['titulo'] = 'Login';

        echo view('login', $data);
	}

	//--------------------------------------------------------------------

}
