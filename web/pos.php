<?php

$input = array();
foreach($_GET as $key => $val) {
  $input[$key] = escapeshellarg($val);
}

$datetime = $input['datetime'];
$lat = $input['lat'];
$lon = $input['lon'];

$obs = 'EARTH';
if (isset($input['obs'])) {
  $obs = $input['obs'];
}

$ref = 'J2000';
if (isset($input['ref'])) {
  $ref = $input['ref'];
}

$cmd = "/usr/local/bin/earth_info isac.meta $obs $ref $datetime $lat $lon";
exec($cmd,$output,$ret);

foreach($output as $line) {
  $data = explode(',',$line);
  echo data2json($data) . "\n";
}

function data2json($data) {
  $str = sprintf('{"%s":[%.2f,%.2f,%.2f]}',
		 str_replace(' BARYCENTER', '', $data[0]),
		 $data[1],
		 $data[2],
		 $data[3]);
  return $str;
}
