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

for src in omods/anim_explode/omod*.blend
do

base=${src%.blend}
base=${base#omods/anim_explode/omod_}

for fr in {51..60}
do

output=Image00${fr}.png

blender -b $src -x 1 -f $fr
convert ./omods/anim_explode/output/$output ./${base}_$(($fr-50)).jpg
convert ./omods/anim_explode/output_spec/$output ./${base}_$(($fr-50))_spec.jpg
convert ./omods/anim_explode/output_z/$output ./${base}_$(($fr-50))_z.jpg
convert ./omods/anim_explode/output_alpha/$output ./${base}_$(($fr-50))_alph.jpg

done

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

