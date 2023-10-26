$(function () {
    $('ul.radio-list, ul.checklist, ul.textbox').each(function (i, el) {
        var questionClass = $(this).attr('class');
        $(this).parent().addClass('question-row').addClass(questionClass);
        if (questionClass == 'radio-list') {
            $(this).find('input[type="radio"]').attr('name', 'radio-question-' + i);
        }
    });

    function checkQuestion(question) {
        var self = question;

        // Single Question.
        if (self.hasClass('radio-list')) {
            if (self.find('input[type="radio"][data-content="1"]:checked').length == 1) {
                self.addClass('text-success');
                self.removeClass('text-danger'); // Eliminar la marca de respuesta incorrecta
                self.find('input[type="radio"]').attr('disabled', true);
            } else {
                self.removeClass('text-success'); // Eliminar la marca de respuesta correcta
                self.addClass('text-danger');
            }
        }
        // Textbox Question.
        if (self.hasClass('textbox')) {
            var textbox = self.find('input[type="text"]');
            var correct_text = String(textbox.data("content")).trim().split("").reverse().join("");
            if (String(textbox.val()).trim().toLowerCase() == correct_text.toLowerCase()) {
                self.addClass('text-success');
                self.removeClass('text-danger'); // Eliminar la marca de respuesta incorrecta
                self.find('input[type="text"]').attr('disabled', true);
            } else {
                self.removeClass('text-success'); // Eliminar la marca de respuesta correcta
                self.addClass('text-danger');
                textbox.parent().find("i.text-correct").html(correct_text);
            }
        }
        // Multiple selection Questions.
        if (self.hasClass('checklist')) {
            var total_corrects = self.find('input[type="checkbox"][data-content="1"]').length;
            var total_incorrects = self.find('input[type="checkbox"][data-content="0"]').length;
            var correct_selected = self.find('input[type="checkbox"][data-content="1"]:checked').length;
            var incorrect_selected = self.find('input[type="checkbox"][data-content="0"]:checked').length;
            var qc = +((correct_selected / total_corrects) - (incorrect_selected / total_incorrects)).toFixed(2);
            if (qc < 0) {
                qc = 0;
            }
            if (qc == 0) {
                self.removeClass('text-success'); // Eliminar la marca de respuesta correcta
                self.addClass('text-danger');
            } else if (qc > 0 && qc < 1) {
                self.addClass('text-warning');
            } else {
                self.addClass('text-success');
                self.removeClass('text-danger'); // Eliminar la marca de respuesta incorrecta
                self.find('input[type="checkbox"]').attr('disabled', true);
            }
        }
    }

    $('li.question-row input').on('change', function () {
        var question = $(this).closest('li.question-row');
        checkQuestion(question);
    });

    $('#reset-questions').on('click', function () {
        $('li.question-row').removeClass('text-success').removeClass('text-danger').removeClass('text-warning');
        $('i.text-correct').html('');
        $('li.question-row input').prop('checked', false);
        $('li.question-row input[type="text"]').val('');
        $('li.question-row input').attr('disabled', false);
    });
});