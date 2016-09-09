FILE(REMOVE_RECURSE
  "CMakeFiles/tender-po-update"
  "../po/hu_HU.po.dummy"
  "../po/fi_FI.po.dummy"
  "../po/pt_PT.po.dummy"
  "../po/de.po.dummy"
  "../po/zh_TW.po.dummy"
  "../po/nb_NO.po.dummy"
  "../po/tr_TR.po.dummy"
  "../po/nl.po.dummy"
  "../po/fr.po.dummy"
  "../po/da.po.dummy"
  "../po/pl_PL.po.dummy"
  "../po/es.po.dummy"
  "../po/it.po.dummy"
  "../po/cs.po.dummy"
  "../po/ru.po.dummy"
  "../po/sv.po.dummy"
  "../po/et.po.dummy"
  "../po/pt_BR.po.dummy"
  "../po/el_GR.po.dummy"
  "../po/pl.po.dummy"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/tender-po-update.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
