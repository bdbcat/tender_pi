FILE(REMOVE_RECURSE
  "CMakeFiles/tender-i18n"
  "hu_HU.mo"
  "fi_FI.mo"
  "pt_PT.mo"
  "de.mo"
  "zh_TW.mo"
  "nb_NO.mo"
  "tr_TR.mo"
  "nl.mo"
  "fr.mo"
  "da.mo"
  "pl_PL.mo"
  "es.mo"
  "it.mo"
  "cs.mo"
  "ru.mo"
  "sv.mo"
  "et.mo"
  "pt_BR.mo"
  "el_GR.mo"
  "pl.mo"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/tender-i18n.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
