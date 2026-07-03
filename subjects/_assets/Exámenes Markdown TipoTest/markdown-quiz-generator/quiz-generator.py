"""
    Developed by Osanda Deshan
"""
import sys
import os

import markdown
from jinja2 import Environment, PackageLoader, select_autoescape

# Render the result including jQuery, Bootstrap.
WRAPPER_RENDER = True
LOOKUP_FOLDER = '../'
OUTPUT_FOLDER = '../'


def render_test(file_name: str, markdown_content: str) -> None:
    """Render quiz in Markdown format to HTML."""

    extensions = ["tables", "app.extensions.checkbox", "app.extensions.radio", "app.extensions.textbox"]

    markdown_lines = markdown_content.split('\n')
    filtered_lines = []
    inside_details = False

    for line in markdown_lines:
        stripped_line = line.strip()
        
        # 1. Detectar si entramos en un bloque <details>
        if stripped_line.startswith("<details>"):
            inside_details = True
            continue  # Saltamos esta línea
            
        # 2. Detectar si salimos de un bloque </details>
        if stripped_line.startswith("</details>"):
            inside_details = False
            continue  # Saltamos esta línea

        # 3. Si estamos dentro de <details>, ignoramos todo el contenido
        if inside_details:
            continue

        # 4. Ignorar las líneas que empiezan con "Explicación:" (insensible a mayúsculas/minúsculas)
        if stripped_line.lower().startswith("explicación:"):
            continue



        # Si pasa todos los filtros, mantenemos la línea original (conservando sus espacios)
        filtered_lines.append(line)

    # Reconstruimos el contenido limpio
    markdown_content = '\n'.join(filtered_lines)

    # El resto de tu código se mantiene exactamente igual
    html = markdown.markdown(markdown_content, extensions=extensions, output_format="html5")
    env = Environment(loader=PackageLoader('app', 'static'), autoescape=select_autoescape(['html', 'xml']))

    javascript = env.get_template('app.js').render()

    test_html = env.get_template('base.html').render(content=html, javascript=javascript)
    if WRAPPER_RENDER:
        test_html = env.get_template('wrapper.html').render(content=test_html)

    with open(os.path.join(OUTPUT_FOLDER, f"{file_name[:-2]}html"), "w+") as f:
        f.write(test_html)

if __name__ == "__main__":
    # Convert all the .md (markdown) files inside the [markdown-quiz-files] folder
    print("-" * 50 + "\nMarkdown Quiz Generator v0.1\n" + "-" * 50)

    WRAPPER_RENDER = 'embed' not in sys.argv

    for file_name in os.listdir(LOOKUP_FOLDER):
        if file_name.endswith('.md'):
            with open(os.path.join(LOOKUP_FOLDER, file_name), "r") as f:
                print(f"Converting to Markdown ({file_name}) ...")
                render_test(file_name, f.read())

    sys.exit(0)
