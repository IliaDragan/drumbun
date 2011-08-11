<?php

/**
 * @file
 */

function cctags_page($item) {
    global   $pager_page_array, $pager_total, $pager_total_items;
    $cctid = $item['cctid'];
    $title = $item['page_title'];
    $amount = $item['page_amount'];
    $mode = $item['page_mode'];
    $vocname = $item['page_vocname'];
    $extra_class = ($item['page_extra_class'])?' '. $item['page_extra_class']:'';
    if ($cctid == NULL) {
        return drupal_not_found();
    }
    $title = ($title=='<none>')?'':$title;
    drupal_set_title($title);
    $terms = cctags_get_level_tags($cctid, 'page');
    $count_terms = 0; //count($terms);
    foreach ($terms as $k => $v) {
    $count_terms += count($v)-3;
    }

    $page = (!isset($_GET['page']) || $amount==0 || $count_terms < $amount)?0:$_GET['page'];
    $content = theme('cctags_level', array('terms' => $terms, 'amount' => $amount, 'page' => $page, 'mode' => $mode, 'vocname' => $vocname, 'out' => 'page'));
    $pager = NULL;
    if ($amount>0 and $count_terms > $amount) {
    $pager_page_array = explode(',', $page);
    $pager_total_items[0] = $count_terms;
    $pager_total[0] = ceil($pager_total_items[0] / $amount);
    $pager_page_array[0] = max(0, min((int)$pager_page_array[0], ((int)$pager_total[0]) - 1));
    $pager = theme('pager',array( NULL, $amount, 0));
    }
    $output = theme('cctags_page', array('cctid' => $cctid, 'extra_class'=>$extra_class, 'content' => $content, 'pager' => $pager));
    return $output;
}

