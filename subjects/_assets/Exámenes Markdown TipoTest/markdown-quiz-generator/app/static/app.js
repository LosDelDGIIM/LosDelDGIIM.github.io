$(function () {
    // Guardar el orden inicial de las preguntas y opciones
    var initialQuestions = [];
    var initialOptions = [];

    // Guardar el orden inicial de las preguntas y opciones al cargar la página
    $('ol').each(function (i, ol) {
        var $ol = $(ol);
        initialQuestions[i] = $ol.children('li').toArray();
    });
    $('ul.radio-list').each(function (i, ul) {
        var $ul = $(ul);
        initialOptions[i] = $ul.children('li').toArray();
    });


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
                self.removeClass('text-warning');
                self.addClass('text-danger');
            } else if (qc > 0 && qc < 1) {
                self.removeClass('text-success'); // Eliminar la marca de respuesta correcta
                self.removeClass('text-danger'); // Eliminar la marca de respuesta incorrecta
                self.addClass('text-warning');
            } else {
                self.removeClass('text-warning'); // Eliminar la marca de respuesta parcialmente correcta
                self.removeClass('text-danger'); // Eliminar la marca de respuesta incorrecta
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

    // Función para mostrar todas las respuestas correctas
    $('#show-answers').on('click', function () {
        $('li.question-row').each(function () {
            var question = $(this);

            // Mostrar respuestas correctas para preguntas de tipo radio
            if (question.hasClass('radio-list')) {
                question.find('input[type="radio"][data-content="1"]').prop('checked', true);
                question.addClass('text-success');
                question.find('input[type="radio"]').attr('disabled', true); // Bloquear inputs
            }

            // Mostrar respuestas correctas para preguntas de tipo checkbox
            if (question.hasClass('checklist')) {
                question.find('input[type="checkbox"][data-content="1"]').prop('checked', true);
                question.addClass('text-success');
                question.find('input[type="checkbox"]').attr('disabled', true); // Bloquear inputs
            }

            // Mostrar respuestas correctas para preguntas de tipo textbox
            if (question.hasClass('textbox')) {
                var textbox = question.find('input[type="text"]');
                var correct_text = String(textbox.data("content")).trim();
                textbox.val(correct_text);
                question.addClass('text-success');
                textbox.attr('disabled', true); // Bloquear inputs
            }
        });
    });

    
    // Función para mezclar las preguntas
    function shuffleQuestions() {
        $('ol').each(function() {
            var ol = $(this);
            var liArr = ol.children('li');
            liArr.sort(function() {
                return (Math.round(Math.random()) - 0.5);
            }).detach().appendTo(ol);
        });
    }

    function shuffleOptions() {
    $('ul.radio-list').each(function() {
        var ul = $(this);
        var liArr = ul.children('li');

        // Verificar si la lista tiene exactamente dos opciones
        if (liArr.length === 2) {
            var options = liArr.map(function() {
                return $(this).text().trim().toLowerCase();
            }).get();

            // Comprobar si las opciones son "verdadero" y "falso" (o "true" y "false")
            if ((options.includes('verdadero') && options.includes('falso')) ||
                (options.includes('v') && options.includes('f')) ||
                (options.includes('t') && options.includes('f')) ||
                (options.includes('Sí') && options.includes('No')) ||
                (options.includes('true') && options.includes('false'))) {
                return; // No mezclar si son Verdadero/Falso
            }
        }

        // Mezclar las opciones si no es un caso de Verdadero/Falso
        liArr.sort(function() {
        return (Math.round(Math.random()) - 0.5);
        }).detach().appendTo(ul);
    });
    }

    // Llamar a las funciones para mezclar las preguntas y las opciones al cargar la página
    shuffleQuestions();
    shuffleOptions();



    // Función para restaurar el orden inicial de preguntas y opciones
    function restoreInitialOrder() {
        // Restaurar preguntas
        $('ol').each(function(i, ol) {
            $(ol).empty();
            $(ol).append(initialQuestions[i]);
        });
        // Restaurar opciones
        $('ul.radio-list').each(function(i, ul) {
            $(ul).empty();
            $(ul).append(initialOptions[i]);
        });
    }
    $('#reorder-questions').on('click', function () {
        restoreInitialOrder();
    });
});