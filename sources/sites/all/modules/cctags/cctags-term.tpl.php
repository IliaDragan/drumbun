<?php
/**
* $term object
* $mode = block or page
* example $term  object
** stdClass Object
**(
**    [tid] => 26
**    [vid] => 3
**    [name] => Drupal 6.*
**    [description] =>
**    [weight] => 1.38629436112
**    [depth] => 0
**    [parents] => Array
**        (
**            [0] => 0
**        )
**
**    [count] => 3
**    [path] => taxonomy/term/26
**    [level] => 5
**    [link] => Drupal 6.*
**)
* if $term-count>0 then
* $term->link = l($term->name, $term->path, array('attributes' => array('class' => "cctags cctags-$mode vid-$term->vid level-$term->level depth-$term->depth count-$term->count ccfilter tooltip", 'title'=>$term->description,'rel' => 'tag')));
* else
* $term->link = "<span class=\"cctags cctags-$mode vid-$term->vid level-$term->level depth-$term->depth count-$term->count\" rel=\"tag\">$term->name</span>"
*/
?>
<?php print render($term) . '&nbsp; '; ?>