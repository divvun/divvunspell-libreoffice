import logging
import unohelper  # type: ignore

import grammar
import spelling

# Uncomment for debugging purposes
logging.basicConfig(filename="/tmp/divvunspell-libreoffice.log", level=logging.DEBUG)

# Register the services
logging.info("Registering services")
try:
    g_ImplementationHelper = unohelper.ImplementationHelper()
    g_ImplementationHelper.addImplementation(
        spelling.SpellChecker,
        spelling.SpellChecker.IMPLEMENTATION_NAME,
        spelling.SpellChecker.SUPPORTED_SERVICE_NAMES,
    )
    g_ImplementationHelper.addImplementation(
        grammar.GrammarChecker,
        grammar.GrammarChecker.IMPLEMENTATION_NAME,
        grammar.GrammarChecker.SUPPORTED_SERVICE_NAMES,
    )
except Exception as e:
    logging.error(e)
