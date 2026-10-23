# The OOGIE_PRESS script automated runs use: menus to NEW GAME, then dialogue, walking, attacks and jumps in Town Square.
menu=$(python -c "print(','.join(f'up@{t:.2f},start@{t+0.75:.2f}' for t in [30+1.5*i for i in range(18)]))")
play=$(python -c "
ev = [f'a@{66 + i * 1.2:.1f}' for i in range(8)]
t = 78
for r in range(12):
    ev += [f'walk@{t}:3', f'x@{t+3.2:.1f}', f'x@{t+3.6:.1f}', f'b@{t+4.0:.1f}', f'a@{t+4.4:.1f}', f'lookl@{t+4.8:.1f}:1', f'sider@{t+6:.1f}:1.5', f'y@{t+7.6:.1f}']
    t += 9
print(','.join(ev))")
export OOGIE_PRESS="$menu,$play"
