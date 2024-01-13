
function buttons(){

    const accordeonButtons = document.querySelectorAll('.accordeon');

    accordeonButtons.forEach(button => {
        button.addEventListener('click', () => {
            const accordeon = button.nextElementSibling;

            if (accordeon.style.display == 'block'){ // Hay que ocultarlo
                accordeon.style.display = 'none';
            }
            else{ // Hay que mostrarlo

                // Cerrar todos los desplegables hijos
                const childAccordeons = accordeon.querySelectorAll('.accordeon');
                childAccordeons.forEach(childAcc => {
                    const childAccordeon = childAcc.nextElementSibling;
                    childAccordeon.style.display = 'none';
                    childAcc.classList.remove("year-remark");
                    childAcc.classList.remove("subject-remark");
                    
                    // Change icon
                    const icon = childAcc.querySelector('i');
                    icon.classList.remove('bi-dash-circle');
                    icon.classList.add('bi-plus-circle');
                });


                accordeon.style.display = 'block';
            }
            
            // Change icon
            const icon = button.querySelector('i');
            icon.classList.toggle("bi-dash-circle");
            icon.classList.toggle("bi-plus-circle");

            
        });
    });
}


// Change the style of the years
function styleYears(){

    const years = document.querySelectorAll('.year');

    years.forEach(year => {
        year.addEventListener('click', () => {
            year.classList.toggle("year-remark");
        });
    });

}

// Change the style of the subjects
function styleSubjects(){

    const subjects = document.querySelectorAll('.subject');

    subjects.forEach(subject => {
        subject.addEventListener('click', () => {
            subject.classList.toggle("subject-remark");
        });
    });
}

function aniade_blank(){
    var yearList = document.getElementById('year-list');
    var anchors = yearList.getElementsByTagName('a');
    for (var i=0; i<anchors.length; i++){
        anchors[i].setAttribute('target', '_blank');
    }
}




// Starts every function
function start(){
    aniade_blank();
    buttons();
    styleYears();
    styleSubjects();
}


window.onload=start;