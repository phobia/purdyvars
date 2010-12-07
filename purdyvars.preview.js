(function($){
    
    $('document').ready(function(){
        $('#edit-purdyvars-prefix').keyup(update);
        $('#edit-purdyvars-suffix').keyup(update);
        $('input[name=purdyvars_overwrite_drupal]').change(update);
        $('<dl><dt><strong>Preview:</strong></dt><dd><code id="purdyvarsPreview"></code></dd><dt><strong>Example usage:</strong></dt><dd><code id="purdyvarsExample"></code></dd></dl>').insertAfter('.form-item-purdyvars-suffix');
        update();
    });
    
    function setPreview() {
        var preview = getPreview();
        $('#purdyvarsPreview').text(preview);
    }
    
    function update() {
        if($('#edit-purdyvars-overwrite-drupal-1:checked').length) {
            $('#edit-fieldnaming').hide();
        } else {
            $('#edit-fieldnaming').show();
            setPreview();
            setExample();
        }
    }

    function setExample() {
        var preview = getPreview();
        var example = '<?php echo ' + preview + '; ?>';
        $('#purdyvarsExample').text(example);
    }
    
    function getPreview() {
        
        var exampleField = 'yourfieldname';
        var prefix = $('#edit-purdyvars-prefix').val();
        var suffix = $('#edit-purdyvars-suffix').val();
        
        var preview = '$' + prefix + exampleField + suffix;
    
        return preview;

    }
    
})(jQuery)