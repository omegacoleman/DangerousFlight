#!/usr/bin/env sh
for src in omods/omod*.blend
do

output=Image0001.png
base=${src%.blend}
base=${base#omods/omod_}


blender -b $src -x 1 -f 1
convert ./omods/output/$output ./${base}.jpg
convert ./omods/output_spec/$output ./${base}_spec.jpg
convert ./omods/output_z/$output ./${base}_z.jpg
convert ./omods/output_alpha/$output ./${base}_alph.jpg

done

rm -rf ./omods/output ./omods/output_spec ./omods/output_z ./omods/output_alpha

echo
echo
echo
echo "Done."

