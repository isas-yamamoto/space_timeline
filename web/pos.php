<?php

$input = array();
foreach($_GET as $key => $val) {
  $input[$key] = escapeshellarg($val);
}

$datetime = str_replace(' ', 'T', gmdate('Y-m-d H:i:s'));
if (isset($input['datetime'])) {
  $datetime = $input['datetime'];
}

$lat = 0;
if (isset($input['lat'])) {
  $lat = $input['lat'];
}
$lon = 0;
if (isset($input['lon'])) {
  $lon = $input['lon'];
}

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

echo "{\n";
echo '  "datetime" : {"' . $output[0] . "\"}\n";
echo '  "location" : [' . "\n";

for($i=1; $i<count($output); $i++) {
  $data = explode(',',$output[$i]);
  echo "    " . data2json($data) . "\n";
}
echo "  ]\n";
echo "}\n";

function data2json($data) {
  $str = sprintf('{"%s":[%.2f,%.2f,%.2f]}',
		 str_replace(' BARYCENTER', '', $data[0]),
		 $data[1],
		 $data[2],
		 $data[3]);
  return $str;
}
