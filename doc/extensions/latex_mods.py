
from sphinx.util.texescape import tex_escape_map
import sphinx.writers.latex

BaseTranslator = sphinx.writers.latex.LaTeXTranslator

class DocTranslator(BaseTranslator):
    
    def visit_caption(self, node):
        print("!"*50)
        caption_idx = node.parent.index(node)
        if caption_idx > 0:
            look_node = node.parent.children[caption_idx - 1]
        else:
            look_node = node.parent

        short_caption = unicode(look_node.get('alt', '')).translate(tex_escape_map)
        if short_caption != "":
            short_caption = '[%s]' % short_caption

        self.in_caption += 1
        self.body.append('\\caption%s{' % short_caption)
        
    def depart_caption(self, node):
        self.body.append('}')
        self.in_caption -= 1
        
        
sphinx.writers.latex.LaTeXTranslator = DocTranslator
