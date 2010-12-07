Purdyvars - simplified field data usage in node templates
=========================================================

Purdyvars is a Drupal module that makes raw field variable values accessible in a tidy way in node templates.

Where you in a node template normally would have to do something like this:
<?php echo $node->field_myfield['und'][0]['safe_value']; ?>

you can now do this:
<?php echo $field_myfield; ?>

If the field has multiple values, you may use the variable as an array:
<ul>
<?php foreach($field_myfield as $foo) :?>
<li><?php echo $foo; ?></li>
<?php endforeach; ?>
</ul>

If the field has multiple values, and you still echo (or print) you will get the first value of the array.

If you for some field wish to get the html Drupal was planning on rendering, you may use this:
<?php echo $field_myfield->render; ?>

To get the label for the field, you may use this:
<?php echo $field_myfield->label; ?>

