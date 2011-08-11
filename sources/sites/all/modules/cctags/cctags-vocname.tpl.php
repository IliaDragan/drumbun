<?php
/**
* $vocname 	-- array vocabulary name
* $vid   	  -- array vocabulary vid
* $terms   	-- array counts terms in current vocabulary
* $mode     -- mixed or group
* $is_out   -- array counts terms in current vocabulary
*/
//dbg($mode);
//dbg($is_out);
?>
<div class="clearfix">
<?php if(isset($vocname)) { ?>
<div class="cctags vocname">
<?php $i=0; foreach($vocname as $key => $name) {
if ($i>0) {$vname = '&nbsp;::&nbsp;'.$name;}
else {$vname = $name;}
$i++;
?>
<?php if(($mode == 'group' && $is_out[$vid[$key]]==1) || $mode == 'mixed') { ?>
<span class="cctags vocname vid-<?php print $vid[$key];?>"><?php print render($vname); ?></span>
<?php } ?>
<?php } ?>
</div>
<?php } ?>
</div>
