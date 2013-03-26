#!/usr/bin/env sh

for src in omods/omod*.blend
do

output=Image0090.png
base=${src%.blend}
base=${base#omods/omod_}


blender -b $src -x 1 -f 90
convert ./omods/output/$output ./${base}.jpg
convert ./omods/output_spec/$output ./${base}_spec.jpg
convert ./omods/output_z/$output ./${base}_z.jpg
convert ./omods/output_alpha/$output ./${base}_alph.jpg

done

rm -rf ./omods/output ./omods/output_spec ./omods/output_z ./omods/output_alpha


# for src in addition/env_blend/*.blend
# do
# 
# f=IMG
# output=${f}0001.jpg
# base=${src%.blend}
# base=${base#addition/env_blend/}
# 
# 
# blender -b $src -o ${f} -F JPEG -x 1 -f 1 
# convert -resize 800x600! ${output} env_${base}.jpg
# 
# rm -f  ${output}
# 
# done

echo
echo
echo
echo "Done."

