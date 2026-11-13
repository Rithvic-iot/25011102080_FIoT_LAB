import os
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.patches as patches

REPO_ROOT = r'c:\Users\RITHVIC RAAJ S\Desktop\IOT-git'

def setup_canvas(title, subtitle, note=''):
    fig, ax = plt.subplots(figsize=(11, 6.5), dpi=160)
    ax.set_xlim(0, 110)
    ax.set_ylim(0, 68)
    ax.axis('off')
    
    # Outer Border & Header
    ax.add_patch(patches.Rectangle((1.5, 1.5), 107, 65, fill=False, edgecolor='#0F172A', lw=2))
    ax.add_patch(patches.Rectangle((1.5, 56.5), 107, 10, fill=True, facecolor='#1E3A8A'))
    ax.text(55, 62.5, 'SHIV NADAR UNIVERSITY CHENNAI - IoT LAB', color='white', fontsize=12, fontweight='bold', ha='center', va='center')
    ax.text(55, 59, f'CIRCUIT SCHEMATIC : {title.upper()}', color='#93C5FD', fontsize=9.5, fontweight='bold', ha='center', va='center')
    
    # Bottom Note
    if note:
        ax.text(55, 3.8, f'Design Note: {note}', fontsize=7.8, style='italic', color='#334155', ha='center')
        
    return fig, ax

def draw_ic(ax, x, y, w, h, name, subtitle='', left_pins=None, right_pins=None, top_pins=None, bottom_pins=None, fill='#F8FAFC', border='#0F172A'):
    ax.add_patch(patches.Rectangle((x, y), w, h, fill=True, facecolor=fill, edgecolor=border, lw=2, zorder=2))
    ax.text(x + w/2, y + h - 3, name, fontsize=10, fontweight='bold', ha='center', va='center', zorder=3, color='#0F172A')
    if subtitle:
        ax.text(x + w/2, y + h - 6.2, subtitle, fontsize=7.8, color='#475569', ha='center', va='center', zorder=3)
        
    pin_coords = {}
    if left_pins:
        for item in left_pins:
            lbl, pnum, py = item[0], item[1], item[2]
            ax.plot([x - 2.5, x], [py, py], 'k-', lw=1.5, zorder=1)
            t = f'{lbl} ({pnum})' if pnum else lbl
            ax.text(x + 1, py, t, fontsize=7.5, va='center', ha='left', color='#1E293B', zorder=3)
            pin_coords[lbl] = (x - 2.5, py)
            
    if right_pins:
        for item in right_pins:
            lbl, pnum, py = item[0], item[1], item[2]
            ax.plot([x + w, x + w + 2.5], [py, py], 'k-', lw=1.5, zorder=1)
            t = f'{lbl} ({pnum})' if pnum else lbl
            ax.text(x + w - 1, py, t, fontsize=7.5, va='center', ha='right', color='#1E293B', zorder=3)
            pin_coords[lbl] = (x + w + 2.5, py)
            
    if top_pins:
        for item in top_pins:
            lbl, pnum, px = item[0], item[1], item[2]
            ax.plot([px, px], [y + h, y + h + 2.5], 'k-', lw=1.5, zorder=1)
            t = f'{lbl} ({pnum})' if pnum else lbl
            ax.text(px, y + h - 2, t, fontsize=7.5, ha='center', va='top', color='#1E293B', zorder=3)
            pin_coords[lbl] = (px, y + h + 2.5)
            
    if bottom_pins:
        for item in bottom_pins:
            lbl, pnum, px = item[0], item[1], item[2]
            ax.plot([px, px], [y, y - 2.5], 'k-', lw=1.5, zorder=1)
            t = f'{lbl} ({pnum})' if pnum else lbl
            ax.text(px, y + 2, t, fontsize=7.5, ha='center', va='bottom', color='#1E293B', zorder=3)
            pin_coords[lbl] = (px, y - 2.5)
            
    return pin_coords

def draw_resistor(ax, x1, y1, x2, y2, label='330Ω', color='#D97706'):
    if abs(y1 - y2) < 0.1: # Horizontal
        mx = (x1 + x2) / 2
        rw = min(abs(x2 - x1) * 0.7, 7)
        rh = 2.4
        ax.plot([x1, mx - rw/2], [y1, y1], 'k-', lw=1.5)
        ax.add_patch(patches.Rectangle((mx - rw/2, y1 - rh/2), rw, rh, facecolor='#FEF3C7', edgecolor=color, lw=1.5, zorder=4))
        ax.plot([mx + rw/2, x2], [y2, y2], 'k-', lw=1.5)
        ax.text(mx, y1, label, fontsize=7.5, fontweight='bold', ha='center', va='center', zorder=5, color='#92400E')
    else: # Vertical
        my = (y1 + y2) / 2
        rh = min(abs(y2 - y1) * 0.7, 7)
        rw = 2.4
        ax.plot([x1, x1], [y1, my + rh/2 if y1 > y2 else my - rh/2], 'k-', lw=1.5)
        ax.add_patch(patches.Rectangle((x1 - rw/2, my - rh/2), rw, rh, facecolor='#FEF3C7', edgecolor=color, lw=1.5, zorder=4))
        ax.plot([x1, x1], [my - rh/2 if y1 > y2 else my + rh/2, y2], 'k-', lw=1.5)
        ax.text(x1 + 1.8, my, label, fontsize=7.5, fontweight='bold', ha='left', va='center', zorder=5, color='#92400E')

def draw_led(ax, x, y, color='#EF4444', label='LED', direction='right'):
    if direction == 'right':
        poly = patches.Polygon([[x, y - 2.5], [x, y + 2.5], [x + 5, y]], closed=True, facecolor=color, edgecolor='#991B1B', lw=1.5, zorder=4)
        ax.add_patch(poly)
        ax.plot([x + 5, x + 5], [y - 2.5, y + 2.5], 'k-', lw=2, zorder=4)
        ax.annotate('', xy=(x + 6, y + 4), xytext=(x + 3, y + 2), arrowprops=dict(arrowstyle='->', lw=1.2, color=color))
        ax.annotate('', xy=(x + 8, y + 3.5), xytext=(x + 5, y + 1.5), arrowprops=dict(arrowstyle='->', lw=1.2, color=color))
        ax.text(x + 2.5, y - 4, label, fontsize=7.5, fontweight='bold', ha='center', color='#1E293B')
        return (x + 5, y)
    elif direction == 'down':
        poly = patches.Polygon([[x - 2.5, y], [x + 2.5, y], [x, y - 5]], closed=True, facecolor=color, edgecolor='#991B1B', lw=1.5, zorder=4)
        ax.add_patch(poly)
        ax.plot([x - 2.5, x + 2.5], [y - 5, y - 5], 'k-', lw=2, zorder=4)
        ax.annotate('', xy=(x + 4, y - 6), xytext=(x + 2, y - 3), arrowprops=dict(arrowstyle='->', lw=1.2, color=color))
        ax.text(x + 3.5, y - 2.5, label, fontsize=7.5, fontweight='bold', ha='left', color='#1E293B')
        return (x, y - 5)

def draw_gnd(ax, x, y, label='GND'):
    ax.plot([x, x], [y + 2, y], 'k-', lw=1.5)
    ax.plot([x - 2.5, x + 2.5], [y, y], 'k-', lw=2)
    ax.plot([x - 1.8, x + 1.8], [y - 0.9, y - 0.9], 'k-', lw=1.5)
    ax.plot([x - 0.9, x + 0.9], [y - 1.8, y - 1.8], 'k-', lw=1)
    if label:
        ax.text(x, y - 3.4, label, fontsize=6.8, ha='center', color='#475569')

def draw_vcc(ax, x, y, label='+5V'):
    ax.plot([x, x], [y - 1.5, y], 'k-', lw=1.5)
    ax.plot([x - 2, x + 2], [y, y], 'k-', lw=2)
    ax.annotate('', xy=(x, y + 2), xytext=(x, y), arrowprops=dict(arrowstyle='->', lw=1.5, color='#DC2626'))
    ax.text(x, y + 3.2, label, fontsize=7.5, fontweight='bold', ha='center', color='#DC2626')

def draw_switch(ax, x1, y1, x2, y2, label='SW (Button)'):
    ax.plot([x1, x1 + 2], [y1, y1], 'k-', lw=1.5)
    ax.plot([x2 - 2, x2], [y2, y2], 'k-', lw=1.5)
    ax.plot([x1 + 2], [y1], 'ko', markersize=3)
    ax.plot([x2 - 2], [y2], 'ko', markersize=3)
    ax.plot([x1 + 2, x2 - 2], [y1, y1 + 3.2], 'k-', lw=1.8)
    ax.text((x1 + x2)/2, y1 + 4.5, label, fontsize=7.5, fontweight='bold', ha='center', color='#0284C7')

def draw_capacitor(ax, x, y1, y2, label='100nF'):
    my = (y1 + y2) / 2
    ax.plot([x, x], [y1, my + 0.8], 'k-', lw=1.5)
    ax.plot([x - 2, x + 2], [my + 0.8, my + 0.8], 'k-', lw=2)
    ax.plot([x - 2, x + 2], [my - 0.8, my - 0.8], 'k-', lw=2)
    ax.plot([x, x], [my - 0.8, y2], 'k-', lw=1.5)
    ax.text(x + 2.5, my, label, fontsize=7, va='center', color='#475569')

def draw_crystal_block(ax, x, y):
    ax.plot([x, x - 3], [y + 2, y + 2], 'k-', lw=1.5)
    ax.plot([x, x - 3], [y - 2, y - 2], 'k-', lw=1.5)
    ax.plot([x - 3, x - 3], [y + 2, y + 1], 'k-', lw=1.5)
    ax.plot([x - 3, x - 3], [y - 2, y - 1], 'k-', lw=1.5)
    ax.plot([x - 4.5, x - 1.5], [y + 1, y + 1], 'k-', lw=1.8)
    ax.add_patch(patches.Rectangle((x - 4, y - 0.7), 2, 1.4, facecolor='#E2E8F0', edgecolor='black', lw=1))
    ax.plot([x - 4.5, x - 1.5], [y - 1, y - 1], 'k-', lw=1.8)
    ax.text(x - 5.5, y, '11.0592 MHz', fontsize=7, ha='right', va='center', color='#334155')

def save_fig(fig, rel_path):
    out_file = os.path.join(REPO_ROOT, rel_path.replace('/', os.sep), 'circuit.png')
    os.makedirs(os.path.dirname(out_file), exist_ok=True)
    fig.savefig(out_file, bbox_inches='tight', dpi=160)
    plt.close(fig)
    print(f'Successfully wrote: {out_file}')

# ==============================================================================
# 8051 TASKS (13)
# ==============================================================================

def gen_8051_task2b():
    fig, ax = setup_canvas('8051 / CAT2 / TASK2B : Bare-Metal LED Blink', 'AT89S52 Bare-Metal GPIO Output with Software Delay', 'P1.0 drives external LED through 330Ω current limiting resistor to GND.')
    left = [('XTAL1', '19', 36), ('XTAL2', '18', 32), ('RST', '9', 24), ('EA/VPP', '31', 18)]
    right = [('P1.0', '1', 30)]
    top = [('VCC', '40', 35)]
    bot = [('GND', '20', 35)]
    p = draw_ic(ax, 20, 12, 30, 36, 'AT89S52', '8051 Microcontroller', left, right, top, bot)
    draw_vcc(ax, p['VCC'][0], 50, '+5V')
    draw_gnd(ax, p['GND'][0], 9.5, 'GND')
    draw_crystal_block(ax, p['XTAL1'][0], 34)
    draw_resistor(ax, p['RST'][0], p['RST'][1], p['RST'][0] - 6, p['RST'][1], '10kΩ')
    draw_gnd(ax, p['RST'][0] - 6, 12)
    # LED
    draw_resistor(ax, p['P1.0'][0], p['P1.0'][1], p['P1.0'][0] + 18, p['P1.0'][1], '330Ω')
    led_cath = draw_led(ax, p['P1.0'][0] + 18, p['P1.0'][1], '#EF4444', 'LED (P1.0)', 'right')
    ax.plot([led_cath[0], led_cath[0] + 6], [led_cath[1], led_cath[1]], 'k-', lw=1.5)
    draw_gnd(ax, led_cath[0] + 6, 16)
    save_fig(fig, '8051/CAT2/TASK2B')

def gen_8051_task3a():
    fig, ax = setup_canvas('8051 / CAT3 / TASK3A : Switch Polling & 4-LED Modes', 'Push Button Input with Debounce & 4-LED Mode Patterns', 'P3.2 is pulled up to +5V (Active LOW); P1.0-P1.3 drive 4 indicator LEDs.')
    left = [('XTAL1', '19', 38), ('XTAL2', '18', 34), ('P3.2/INT0', '12', 24)]
    right = [('P1.0', '1', 40), ('P1.1', '2', 34), ('P1.2', '3', 28), ('P1.3', '4', 22)]
    top = [('VCC', '40', 35)]
    bot = [('GND', '20', 35)]
    p = draw_ic(ax, 20, 12, 30, 36, 'AT89S52', '8051 Microcontroller', left, right, top, bot)
    draw_vcc(ax, p['VCC'][0], 50, '+5V')
    draw_gnd(ax, p['GND'][0], 9.5, 'GND')
    draw_crystal_block(ax, p['XTAL1'][0], 36)
    # Switch on P3.2
    ax.plot([p['P3.2/INT0'][0], p['P3.2/INT0'][0] - 3], [p['P3.2/INT0'][1], p['P3.2/INT0'][1]], 'k-', lw=1.5)
    draw_vcc(ax, p['P3.2/INT0'][0] - 3, 38, '+5V')
    draw_resistor(ax, p['P3.2/INT0'][0] - 3, 36, p['P3.2/INT0'][0] - 3, 24, '10kΩ')
    draw_switch(ax, p['P3.2/INT0'][0] - 3, 24, p['P3.2/INT0'][0] - 12, 24, 'SW1')
    draw_gnd(ax, p['P3.2/INT0'][0] - 12, 14)
    # 4 LEDs
    colors = ['#EF4444', '#10B981', '#3B82F6', '#F59E0B']
    for idx, pin_name in enumerate(['P1.0', 'P1.1', 'P1.2', 'P1.3']):
        py = p[pin_name][1]
        draw_resistor(ax, p[pin_name][0], py, p[pin_name][0] + 16, py, '330Ω')
        lc = draw_led(ax, p[pin_name][0] + 16, py, colors[idx], f'LED{idx+1}', 'right')
        ax.plot([lc[0], 98], [py, py], 'k-', lw=1.5)
    ax.plot([98, 98], [22, 40], 'k-', lw=1.5)
    draw_gnd(ax, 98, 14)
    save_fig(fig, '8051/CAT3/TASK3A')

def gen_8051_task4a():
    fig, ax = setup_canvas('8051 / CAT4 / TASK4A : 4x4 Keypad & 7-Segment Display', 'Matrix Keypad Scanning (Port 2) & Common-Cathode 7-Seg Feedback (Port 0)', 'Port 0 has external 10kΩ pull-up SIP resistor pack; Port 2 scans 4x4 matrix keypad.')
    left = [('P2.0 (R1)', '21', 40), ('P2.1 (R2)', '22', 36), ('P2.2 (R3)', '23', 32), ('P2.3 (R4)', '24', 28),
            ('P2.4 (C1)', '25', 24), ('P2.5 (C2)', '26', 20), ('P2.6 (C3)', '27', 16), ('P2.7 (C4)', '28', 12)]
    right = [('P0.0 (a)', '39', 42), ('P0.1 (b)', '38', 38), ('P0.2 (c)', '37', 34), ('P0.3 (d)', '36', 30),
             ('P0.4 (e)', '35', 26), ('P0.5 (f)', '34', 22), ('P0.6 (g)', '33', 18), ('P3.0 (LED)', '10', 12)]
    p = draw_ic(ax, 38, 8, 34, 42, 'AT89S52', '8051 MCU', left, right)
    draw_vcc(ax, 55, 51.5, '+5V')
    draw_gnd(ax, 55, 5.5, 'GND')
    # Keypad
    ax.add_patch(patches.Rectangle((6, 12), 20, 32, facecolor='#F1F5F9', edgecolor='#475569', lw=2))
    ax.text(16, 41, '4x4 KEYPAD', fontsize=8.5, fontweight='bold', ha='center')
    for r in range(4):
        for c in range(4):
            val = str(r*4 + c + 1) if r*4+c+1 <= 9 else ['0', 'A', 'B', 'C', 'D', '*', '#'][r*4+c-9]
            ax.add_patch(patches.Circle((9 + c*4.5, 36 - r*6), 1.5, facecolor='#E2E8F0', edgecolor='#64748B'))
            ax.text(9 + c*4.5, 36 - r*6, val, fontsize=6.5, ha='center', va='center')
    ax.annotate('', xy=(35.5, 26), xytext=(26, 26), arrowprops=dict(arrowstyle='<->', lw=2, color='#0284C7'))
    ax.text(31, 28, '8-bit Bus', fontsize=7.5, color='#0284C7', ha='center', fontweight='bold')
    # 7-Seg
    ax.add_patch(patches.Rectangle((84, 16), 20, 30, facecolor='#1E293B', edgecolor='#0F172A', lw=2))
    ax.text(94, 43, '7-SEG DISPLAY', fontsize=8.5, fontweight='bold', color='white', ha='center')
    ax.text(94, 30, '8', fontsize=32, fontweight='bold', color='#EF4444', ha='center', va='center')
    ax.text(94, 18, 'CC (Common Cathode)', fontsize=6.5, color='#94A3B8', ha='center')
    ax.annotate('', xy=(84, 30), xytext=(74.5, 30), arrowprops=dict(arrowstyle='->', lw=2, color='#DC2626'))
    ax.text(79, 32, 'P0 Bus', fontsize=7.5, color='#DC2626', ha='center', fontweight='bold')
    save_fig(fig, '8051/CAT4/TASK4A')

def gen_8051_task5a():
    fig, ax = setup_canvas('8051 / CAT5 / TASK5A : Timer 0 1ms Periodic Interrupt', 'Internal Timer 0 Mode 1 (16-bit) Time Base with LED & Scope Test Point', 'TH0=0xFC, TL0=0x66 generates exact 1ms tick at 11.0592 MHz crystal frequency.')
    left = [('XTAL1', '19', 36), ('XTAL2', '18', 32), ('RST', '9', 24)]
    right = [('P1.0', '1', 30)]
    p = draw_ic(ax, 20, 14, 30, 34, 'AT89S52', '8051 Microcontroller', left, right)
    draw_vcc(ax, 35, 50, '+5V')
    draw_gnd(ax, 35, 11, 'GND')
    draw_crystal_block(ax, p['XTAL1'][0], 34)
    ax.plot([p['P1.0'][0], 70], [30, 30], 'k-', lw=1.5)
    ax.plot([60], [30], 'ko', markersize=4)
    ax.plot([60, 60], [30, 42], 'k-', lw=1.5)
    ax.add_patch(patches.Rectangle((54, 42), 24, 8, facecolor='#FEF08A', edgecolor='#CA8A04', lw=1.5))
    ax.text(66, 46.5, 'DSO TEST POINT (TP1)', fontsize=7.5, fontweight='bold', ha='center', color='#854D0E')
    ax.text(66, 43.5, 'Measure 1.000 ms Tick', fontsize=7, ha='center', color='#854D0E')
    draw_resistor(ax, 70, 30, 84, 30, '330Ω')
    lc = draw_led(ax, 84, 30, '#10B981', 'LED (1s Toggle)', 'right')
    draw_gnd(ax, lc[0] + 6, 16)
    ax.plot([lc[0], lc[0] + 6], [lc[1], lc[1]], 'k-', lw=1.5)
    save_fig(fig, '8051/CAT5/TASK5A')

def gen_8051_task5b1():
    fig, ax = setup_canvas('8051 / CAT5 / TASK5B.1 : Software PWM Discrete Duty Cycles', 'Variable Duty-Cycle PWM Generation (25%, 50%, 75%) via Timer 0', 'Software counter slices 1ms Timer 0 interval into 10 discrete PWM steps.')
    left = [('XTAL1', '19', 36), ('XTAL2', '18', 32)]
    right = [('P1.0', '1', 30)]
    p = draw_ic(ax, 20, 14, 30, 34, 'AT89S52', '8051 Microcontroller', left, right)
    draw_vcc(ax, 35, 50, '+5V')
    draw_gnd(ax, 35, 11, 'GND')
    draw_crystal_block(ax, p['XTAL1'][0], 34)
    draw_resistor(ax, p['P1.0'][0], 30, 68, 30, '330Ω')
    lc = draw_led(ax, 68, 30, '#3B82F6', 'PWM LED', 'right')
    draw_gnd(ax, lc[0] + 6, 16)
    ax.plot([lc[0], lc[0] + 6], [lc[1], lc[1]], 'k-', lw=1.5)
    ax.add_patch(patches.Rectangle((62, 10), 40, 14, facecolor='#0F172A', edgecolor='#334155', lw=1.5))
    ax.text(82, 21.5, 'OUTPUT PWM WAVEFORM', fontsize=7.5, color='#38BDF8', fontweight='bold', ha='center')
    ax.plot([66, 70, 70, 76, 76, 82, 82, 88, 88, 94, 94, 98],
            [13, 13, 18, 18, 13, 13, 18, 18, 13, 13, 18, 18], color='#4ADE80', lw=2)
    ax.text(82, 11, 'Duty: 25% / 50% / 75% @ 100 Hz', fontsize=6.5, color='#94A3B8', ha='center')
    save_fig(fig, '8051/CAT5/TASK5B/TASK5B.1')

def gen_8051_task5b2():
    fig, ax = setup_canvas('8051 / CAT5 / TASK5B.2 : Dynamic Breathing LED with RC Filter', 'Smooth 0-100% PWM Brightness Breathing Modulation with Analog RC Filter', 'RC filter (R=1kΩ, C=10µF) converts high-frequency PWM pulse train into smooth analog DC voltage.')
    left = [('XTAL1', '19', 36), ('XTAL2', '18', 32)]
    right = [('P1.0', '1', 32)]
    p = draw_ic(ax, 20, 14, 30, 34, 'AT89S52', '8051 Microcontroller', left, right)
    draw_vcc(ax, 35, 50, '+5V')
    draw_gnd(ax, 35, 11, 'GND')
    draw_crystal_block(ax, p['XTAL1'][0], 34)
    ax.plot([p['P1.0'][0], 58], [32, 32], 'k-', lw=1.5)
    draw_resistor(ax, 58, 32, 72, 32, '1 kΩ')
    ax.plot([72], [32], 'ko', markersize=4)
    ax.plot([72, 72], [32, 24], 'k-', lw=1.5)
    draw_capacitor(ax, 72, 24, 16, '10 µF')
    draw_gnd(ax, 72, 13)
    draw_resistor(ax, 72, 32, 86, 32, '330Ω')
    lc = draw_led(ax, 86, 32, '#EC4899', 'BREATHING LED', 'right')
    draw_gnd(ax, lc[0] + 6, 16)
    ax.plot([lc[0], lc[0] + 6], [lc[1], lc[1]], 'k-', lw=1.5)
    save_fig(fig, '8051/CAT5/TASK5B/TASK5B.2')

def gen_8051_task5b3():
    fig, ax = setup_canvas('8051 / CAT5 / TASK5B.3 : Dual-Channel Software PWM Generator', 'Independent Phase & Duty Cycle Outputs on P1.0 and P1.1', 'Channel 1 generates 30% duty cycle (Red); Channel 2 generates 70% duty cycle (Green).')
    left = [('XTAL1', '19', 36), ('XTAL2', '18', 32)]
    right = [('P1.0 (CH1)', '1', 36), ('P1.1 (CH2)', '2', 24)]
    p = draw_ic(ax, 20, 14, 30, 34, 'AT89S52', '8051 Microcontroller', left, right)
    draw_vcc(ax, 35, 50, '+5V')
    draw_gnd(ax, 35, 11, 'GND')
    draw_crystal_block(ax, p['XTAL1'][0], 34)
    draw_resistor(ax, p['P1.0 (CH1)'][0], 36, 75, 36, '330Ω')
    lc1 = draw_led(ax, 75, 36, '#EF4444', 'LED 1 (30% Duty)', 'right')
    draw_gnd(ax, lc1[0] + 6, 16)
    ax.plot([lc1[0], lc1[0] + 6], [lc1[1], lc1[1]], 'k-', lw=1.5)
    draw_resistor(ax, p['P1.1 (CH2)'][0], 24, 75, 24, '330Ω')
    lc2 = draw_led(ax, 75, 24, '#10B981', 'LED 2 (70% Duty)', 'right')
    draw_gnd(ax, lc2[0] + 6, 16)
    ax.plot([lc2[0], lc2[0] + 6], [lc2[1], lc2[1]], 'k-', lw=1.5)
    save_fig(fig, '8051/CAT5/TASK5B/TASK5B.3')

def gen_8051_task5c():
    fig, ax = setup_canvas('8051 / CAT5 / TASK5C : Stepper Motor via ULN2003 Darlington Driver', '4-Phase Unipolar Stepper Motor (28BYJ-48) Commutation via Port 2', 'ULN2003 sinks current through coils A, B, C, D in 4-step sequence powered by external +5V.')
    right = [('P2.0 (IN1)', '21', 40), ('P2.1 (IN2)', '22', 34), ('P2.2 (IN3)', '23', 28), ('P2.3 (IN4)', '24', 22)]
    p1 = draw_ic(ax, 15, 14, 26, 34, 'AT89S52', '8051 MCU', right_pins=right)
    u_left = [('IN1', '1', 40), ('IN2', '2', 34), ('IN3', '3', 28), ('IN4', '4', 22)]
    u_right = [('OUT1', '16', 40), ('OUT2', '15', 34), ('OUT3', '14', 28), ('OUT4', '13', 22)]
    p2 = draw_ic(ax, 50, 14, 22, 34, 'ULN2003', 'Darlington Array', left_pins=u_left, right_pins=u_right)
    for py in [40, 34, 28, 22]:
        ax.plot([43.5, 47.5], [py, py], 'k-', lw=1.5)
    ax.add_patch(patches.Circle((92, 31), 11, facecolor='#FEF3C7', edgecolor='#B45309', lw=2))
    ax.text(92, 34, '28BYJ-48', fontsize=9, fontweight='bold', color='#78350F', ha='center')
    ax.text(92, 31, 'STEPPER', fontsize=8, color='#78350F', ha='center')
    ax.text(92, 28, '5V 4-Phase', fontsize=7, color='#78350F', ha='center')
    for idx, py in enumerate([40, 34, 28, 22]):
        ax.plot([74.5, 82], [py, py], 'k-', lw=1.5)
        ax.plot([82, 85], [py, 35 - idx*3], 'k-', lw=1.5)
    draw_vcc(ax, 61, 50, '+5V (Ext)')
    draw_gnd(ax, 61, 11, 'GND')
    save_fig(fig, '8051/CAT5/TASK5C')

def gen_8051_task6a():
    fig, ax = setup_canvas('8051 / CAT6 / TASK6A : UART Serial Transmission (9600-8-N-1)', 'UART Hardware Driver Sending Strings to PC PuTTY Terminal via CP2102', 'Baud rate generated by Timer 1 in 8-bit auto-reload mode (TH1=0xFD for 9600 baud @ 11.0592 MHz).')
    left = [('XTAL1', '19', 36), ('XTAL2', '18', 32)]
    right = [('TXD (P3.1)', '11', 34), ('GND', '20', 22)]
    p = draw_ic(ax, 18, 14, 28, 34, 'AT89S52', '8051 Microcontroller', left_pins=left, right_pins=right)
    draw_crystal_block(ax, p['XTAL1'][0], 34)
    draw_vcc(ax, 32, 50, '+5V')
    c_left = [('RXD', '1', 34), ('GND', '2', 22)]
    c_right = [('USB D+', '3', 34), ('USB D-', '4', 28)]
    p_cp = draw_ic(ax, 58, 16, 22, 28, 'CP2102', 'USB-to-TTL Bridge', left_pins=c_left, right_pins=c_right)
    ax.plot([48.5, 55.5], [34, 34], 'r-', lw=2)
    ax.text(52, 36, 'TX->RX', fontsize=7.5, color='#DC2626', fontweight='bold', ha='center')
    ax.plot([48.5, 55.5], [22, 22], 'k-', lw=1.5)
    ax.add_patch(patches.Rectangle((90, 18), 16, 24, facecolor='#1E293B', edgecolor='#0F172A', lw=2))
    ax.text(98, 35, 'HOST PC', fontsize=8.5, fontweight='bold', color='white', ha='center')
    ax.text(98, 30, 'PuTTY Terminal', fontsize=7.5, color='#38BDF8', ha='center')
    ax.text(98, 25, '9600 Baud', fontsize=7, color='#94A3B8', ha='center')
    ax.plot([82.5, 90], [34, 34], 'k-', lw=1.5)
    ax.plot([82.5, 90], [28, 28], 'k-', lw=1.5)
    save_fig(fig, '8051/CAT6/TASK6A')

def gen_8051_task6b():
    fig, ax = setup_canvas('8051 / CAT6 / TASK6B : Full-Duplex UART Echo & Ring Buffer', 'Bidirectional UART Link with PC Terminal and Receive Activity LED', 'Interrupt 4 (Serial ISR) receives incoming bytes into a circular ring buffer and echoes back.')
    right = [('TXD (P3.1)', '11', 36), ('RXD (P3.0)', '10', 28), ('P1.0 (LED)', '1', 20)]
    p = draw_ic(ax, 18, 12, 28, 38, 'AT89S52', '8051 MCU', right_pins=right)
    draw_vcc(ax, 32, 51.5, '+5V')
    draw_gnd(ax, 32, 9.5, 'GND')
    c_left = [('RXD', '1', 36), ('TXD', '2', 28)]
    draw_ic(ax, 58, 18, 20, 26, 'CP2102', 'USB-to-TTL', left_pins=c_left)
    ax.plot([48.5, 55.5], [36, 36], 'r-', lw=1.8)
    ax.text(52, 38, 'TX -> RX', fontsize=7.5, color='#DC2626', ha='center')
    ax.plot([48.5, 55.5], [28, 28], 'b-', lw=1.8)
    ax.text(52, 25.5, 'RX <- TX', fontsize=7.5, color='#2563EB', ha='center')
    ax.add_patch(patches.Rectangle((88, 20), 18, 22, facecolor='#1E293B', edgecolor='#0F172A', lw=2))
    ax.text(97, 34, 'PuTTY (PC)', fontsize=8.5, fontweight='bold', color='white', ha='center')
    ax.text(97, 28, 'Interactive Echo', fontsize=7.5, color='#34D399', ha='center')
    ax.plot([80.5, 88], [31, 31], 'k-', lw=2)
    draw_resistor(ax, p['P1.0 (LED)'][0], 20, 68, 20, '330Ω')
    lc = draw_led(ax, 68, 20, '#F59E0B', 'RX ACT', 'right')
    draw_gnd(ax, lc[0] + 6, 14)
    ax.plot([lc[0], lc[0] + 6], [lc[1], lc[1]], 'k-', lw=1.5)
    save_fig(fig, '8051/CAT6/TASK6B')

def gen_8051_task7a():
    fig, ax = setup_canvas('8051 / CAT7 / TASK7A : 16x2 Character LCD Driver (4-Bit)', 'HD44780 16x2 Alphanumeric LCD Interfacing via Port 2 in 4-Bit Mode', 'D4-D7 on P2.4-P2.7; Control RS=P2.0, RW=GND, EN=P2.1. Contrast set by 10kΩ Potentiometer.')
    right = [('P2.0 (RS)', '21', 42), ('P2.1 (EN)', '22', 36),
             ('P2.4 (D4)', '25', 30), ('P2.5 (D5)', '26', 24), ('P2.6 (D6)', '27', 18), ('P2.7 (D7)', '28', 12)]
    p = draw_ic(ax, 16, 8, 28, 42, 'AT89S52', '8051 Microcontroller', right_pins=right)
    draw_vcc(ax, 30, 51.5, '+5V')
    draw_gnd(ax, 30, 5.5, 'GND')
    l_left = [('RS', '4', 42), ('EN', '6', 36),
              ('D4', '11', 30), ('D5', '12', 24), ('D6', '13', 18), ('D7', '14', 12)]
    draw_ic(ax, 64, 8, 38, 42, 'HD44780 16x2 LCD', 'Alphanumeric Liquid Crystal Display', left_pins=l_left)
    for py in [42, 36, 30, 24, 18, 12]:
        ax.plot([46.5, 61.5], [py, py], 'k-', lw=1.5)
    ax.add_patch(patches.Rectangle((70, 22), 26, 12, facecolor='#86EFAC', edgecolor='#15803D', lw=1.5))
    ax.text(83, 29, 'HELLO, 8051!', fontsize=9, fontfamily='monospace', color='#14532D', ha='center', fontweight='bold')
    ax.text(83, 24, '4-BIT BUS MODE', fontsize=7, fontfamily='monospace', color='#14532D', ha='center')
    draw_gnd(ax, 83, 5.5, 'RW=GND')
    save_fig(fig, '8051/CAT7/TASK7A')

def gen_8051_task7b():
    fig, ax = setup_canvas('8051 / CAT7 / TASK7B : 16x2 LCD Dynamic Value Counter', 'Interactive Increment/Decrement Counter with Push Buttons & 16x2 LCD', 'P3.2 (INC) and P3.3 (DEC) buttons trigger numeric display updates via software debounce.')
    left = [('P3.2 (INC)', '12', 36), ('P3.3 (DEC)', '13', 24)]
    right = [('RS (P2.0)', '21', 40), ('EN (P2.1)', '22', 34), ('D4-D7', '25-28', 22)]
    p = draw_ic(ax, 32, 10, 28, 38, 'AT89S52', '8051 MCU', left_pins=left, right_pins=right)
    draw_switch(ax, 12, 36, 29.5, 36, 'INC (+)')
    draw_gnd(ax, 12, 31)
    draw_switch(ax, 12, 24, 29.5, 24, 'DEC (-)')
    draw_gnd(ax, 12, 19)
    l_left = [('RS', '4', 40), ('EN', '6', 34), ('D4-D7', '11-14', 22)]
    draw_ic(ax, 72, 10, 32, 38, '16x2 LCD', 'HD44780', left_pins=l_left)
    ax.plot([62.5, 69.5], [40, 40], 'k-', lw=1.5)
    ax.plot([62.5, 69.5], [34, 34], 'k-', lw=1.5)
    ax.plot([62.5, 69.5], [22, 22], 'k-', lw=2)
    ax.text(66, 24, '4-bit Bus', fontsize=7.5, ha='center', color='#0284C7', fontweight='bold')
    ax.add_patch(patches.Rectangle((76, 24), 24, 10, facecolor='#86EFAC', edgecolor='#15803D', lw=1.5))
    ax.text(88, 30, 'Count: 0042', fontsize=9, fontfamily='monospace', color='#14532D', ha='center', fontweight='bold')
    save_fig(fig, '8051/CAT7/TASK7B')

def gen_8051_task7c():
    fig, ax = setup_canvas('8051 / CAT7 / TASK7C : 4x4 Keypad & LCD Character Movement', 'Directional Character Navigation across 16x2 Display using Keypad', 'Key 2 (Up), 8 (Down), 4 (Left), 6 (Right) control the position of cursor on HD44780 display.')
    left = [('P1 (Keypad)', '1-8', 26)]
    right = [('P2 (LCD Bus)', '21-28', 26)]
    p = draw_ic(ax, 40, 12, 28, 34, 'AT89S52', '8051 MCU', left_pins=left, right_pins=right)
    ax.add_patch(patches.Rectangle((10, 14), 20, 28, facecolor='#F1F5F9', edgecolor='#475569', lw=2))
    ax.text(20, 38, 'KEYPAD', fontsize=8.5, fontweight='bold', ha='center')
    ax.text(20, 32, '[2] UP', fontsize=7, color='#2563EB', ha='center', fontweight='bold')
    ax.text(14, 26, '[4] L', fontsize=7, color='#2563EB', ha='center', fontweight='bold')
    ax.text(26, 26, '[6] R', fontsize=7, color='#2563EB', ha='center', fontweight='bold')
    ax.text(20, 20, '[8] DN', fontsize=7, color='#2563EB', ha='center', fontweight='bold')
    ax.annotate('', xy=(37.5, 26), xytext=(30, 26), arrowprops=dict(arrowstyle='<->', lw=2, color='#0284C7'))
    ax.add_patch(patches.Rectangle((78, 14), 28, 28, facecolor='#1E293B', edgecolor='#0F172A', lw=2))
    ax.text(92, 38, '16x2 LCD', fontsize=9, fontweight='bold', color='white', ha='center')
    ax.add_patch(patches.Rectangle((80, 20), 24, 12, facecolor='#86EFAC', edgecolor='#15803D', lw=1.5))
    ax.text(84, 27, '*', fontsize=14, fontfamily='monospace', color='#DC2626', fontweight='bold')
    ax.text(92, 23, 'Pos: (row 0, col 2)', fontsize=6.5, fontfamily='monospace', color='#14532D', ha='center')
    ax.annotate('', xy=(78, 26), xytext=(70.5, 26), arrowprops=dict(arrowstyle='->', lw=2, color='#10B981'))
    save_fig(fig, '8051/CAT7/TASK7C')

# ==============================================================================
# STM32 TASKS (15)
# ==============================================================================

def gen_stm32_task8a():
    fig, ax = setup_canvas('STM32 / CAT8 / TASK8A : GPIO Input & Output Control', 'External Push Button Input (PA0) and LED Output (PA5)', 'PA0 configured with internal/external pull-up (Active LOW); PA5 drives LED via 330Ω resistor.')
    left = [('PA0 (SW)', 'A0', 30), ('NRST', 'RST', 20)]
    right = [('PA5 (LED)', 'A5', 30), ('PC13', 'C13', 20)]
    p = draw_ic(ax, 32, 10, 36, 40, 'STM32F103C8T6', 'ARM Cortex-M3 (Blue Pill)', left_pins=left, right_pins=right)
    draw_vcc(ax, 50, 51.5, '+3.3V')
    draw_gnd(ax, 50, 7.5, 'GND')
    draw_switch(ax, 12, 30, 29.5, 30, 'USER BUTTON')
    draw_gnd(ax, 12, 25)
    draw_vcc(ax, 29.5, 42, '+3.3V')
    draw_resistor(ax, 29.5, 40, 29.5, 30, '10kΩ')
    draw_resistor(ax, p['PA5 (LED)'][0], 30, 85, 30, '330Ω')
    lc = draw_led(ax, 85, 30, '#10B981', 'EXT LED (PA5)', 'right')
    draw_gnd(ax, lc[0] + 6, 16)
    ax.plot([lc[0], lc[0] + 6], [lc[1], lc[1]], 'k-', lw=1.5)
    save_fig(fig, 'STM32/CAT8/TASK8A')

def gen_stm32_task8b():
    fig, ax = setup_canvas('STM32 / CAT8 / TASK8B : Event Toggle & Hardware RC Debounce', 'Push Button Input with RC Low-Pass Filter Debouncing into STM32 PA0', 'Hardware RC debounce filter (R=10kΩ, C=100nF) eliminates contact bounce spikes on PA0.')
    left = [('PA0 (EXTI0)', 'A0', 30)]
    right = [('PA5 (LED)', 'A5', 30)]
    p = draw_ic(ax, 40, 12, 32, 36, 'STM32F103C8T6', 'ARM Cortex-M3', left_pins=left, right_pins=right)
    draw_vcc(ax, 56, 49.5, '+3.3V')
    draw_gnd(ax, 56, 9.5, 'GND')
    ax.plot([p['PA0 (EXTI0)'][0], 28], [30, 30], 'k-', lw=1.5)
    ax.plot([28], [30], 'ko', markersize=4)
    draw_capacitor(ax, 28, 30, 20, '100nF')
    draw_gnd(ax, 28, 17)
    draw_switch(ax, 10, 30, 28, 30, 'SW1')
    draw_gnd(ax, 10, 25)
    draw_vcc(ax, 28, 42, '+3.3V')
    draw_resistor(ax, 28, 40, 28, 30, '10kΩ')
    draw_resistor(ax, p['PA5 (LED)'][0], 30, 88, 30, '330Ω')
    lc = draw_led(ax, 88, 30, '#3B82F6', 'TOGGLE LED', 'right')
    draw_gnd(ax, lc[0] + 6, 16)
    ax.plot([lc[0], lc[0] + 6], [lc[1], lc[1]], 'k-', lw=1.5)
    save_fig(fig, 'STM32/CAT8/TASK8B')

def gen_stm32_task8c():
    fig, ax = setup_canvas('STM32 / CAT8 / TASK8C : Press Duration Classifier (Short vs Long)', 'Short Press (<1s) Toggles LED; Long Press (>=1s) Activates Blinking Mode', 'SysTick millisecond counter evaluates duration elapsed between push button press and release.')
    left = [('PA0 (INPUT)', 'A0', 32)]
    right = [('PA5 (OUTPUT)', 'A5', 32)]
    p = draw_ic(ax, 35, 12, 36, 36, 'STM32F103C8T6', 'ARM Cortex-M3 MCU', left_pins=left, right_pins=right)
    draw_vcc(ax, 53, 49.5, '+3.3V')
    draw_gnd(ax, 53, 9.5, 'GND')
    draw_switch(ax, 14, 32, 32.5, 32, 'MODE SW')
    draw_gnd(ax, 14, 27)
    draw_vcc(ax, 32.5, 44, '+3.3V')
    draw_resistor(ax, 32.5, 42, 32.5, 32, '10kΩ')
    draw_resistor(ax, p['PA5 (OUTPUT)'][0], 32, 86, 32, '330Ω')
    lc = draw_led(ax, 86, 32, '#EF4444', 'STATUS LED', 'right')
    draw_gnd(ax, lc[0] + 6, 16)
    ax.plot([lc[0], lc[0] + 6], [lc[1], lc[1]], 'k-', lw=1.5)
    ax.add_patch(patches.Rectangle((40, 14), 26, 10, facecolor='#FEF3C7', edgecolor='#D97706', lw=1))
    ax.text(53, 20.5, 'T < 1s : Toggle State', fontsize=7, color='#78350F', ha='center', fontweight='bold')
    ax.text(53, 17, 'T ≥ 1s : 5Hz Continuous Blink', fontsize=7, color='#78350F', ha='center', fontweight='bold')
    save_fig(fig, 'STM32/CAT8/TASK8C')

def gen_stm32_task9a():
    fig, ax = setup_canvas('STM32 / CAT9 / TASK9A : USART1 Echo & Line Termination', 'High-Speed USART1 (PA9 TX, PA10 RX) Communicating with PC at 115200 Baud', 'Evaluates \\r (CR) and \\n (LF) character sequences on host serial terminal.')
    right = [('USART1_TX (PA9)', 'A9', 36), ('USART1_RX (PA10)', 'A10', 26), ('GND', 'G', 16)]
    p = draw_ic(ax, 16, 10, 32, 38, 'STM32F103C8T6', 'ARM Cortex-M3 (Blue Pill)', right_pins=right)
    draw_vcc(ax, 32, 50, '+3.3V')
    c_left = [('RXD', '1', 36), ('TXD', '2', 26), ('GND', 'G', 16)]
    c_right = [('USB D+', '3', 34), ('USB D-', '4', 28)]
    p_cp = draw_ic(ax, 60, 10, 22, 38, 'CP2102', 'USB-to-UART', left_pins=c_left, right_pins=c_right)
    ax.plot([50.5, 57.5], [36, 36], 'r-', lw=2)
    ax.text(54, 38, 'TX -> RX', fontsize=7.5, color='#DC2626', ha='center')
    ax.plot([50.5, 57.5], [26, 26], 'b-', lw=2)
    ax.text(54, 23.5, 'RX <- TX', fontsize=7.5, color='#2563EB', ha='center')
    ax.plot([50.5, 57.5], [16, 16], 'k-', lw=1.5)
    ax.add_patch(patches.Rectangle((92, 16), 15, 26, facecolor='#1E293B', edgecolor='#0F172A', lw=2))
    ax.text(99.5, 36, 'HOST PC', fontsize=8.5, fontweight='bold', color='white', ha='center')
    ax.text(99.5, 30, 'PuTTY Terminal', fontsize=7.5, color='#38BDF8', ha='center')
    ax.text(99.5, 24, '115200-8-N-1', fontsize=7, color='#94A3B8', ha='center')
    save_fig(fig, 'STM32/CAT9/TASK9A')

def gen_stm32_task9b():
    fig, ax = setup_canvas('STM32 / CAT9 / TASK9B : UART String Command Parser', 'Terminal Commands ("> LED ON", "> LED OFF", "> LED TOGGLE") via USART1', 'On-board LED (PC13) and external LED (PA5) actuate based on incoming text commands.')
    right = [('USART1_TX (PA9)', 'A9', 38), ('USART1_RX (PA10)', 'A10', 32),
             ('LED_EXT (PA5)', 'A5', 22), ('LED_ONBOARD (PC13)', 'C13', 14)]
    p = draw_ic(ax, 20, 8, 34, 42, 'STM32F103C8T6', 'ARM Cortex-M3', right_pins=right)
    draw_vcc(ax, 37, 51.5, '+3.3V')
    ax.add_patch(patches.Rectangle((66, 28), 16, 18, facecolor='#F8FAFC', edgecolor='#0F172A', lw=1.5))
    ax.text(74, 41, 'USB-TTL', fontsize=8.5, fontweight='bold', ha='center')
    ax.text(74, 37, 'CP2102', fontsize=7.5, color='#475569', ha='center')
    ax.plot([56.5, 66], [38, 38], 'r-', lw=1.8)
    ax.plot([56.5, 66], [32, 32], 'b-', lw=1.8)
    ax.add_patch(patches.Rectangle((90, 26), 18, 22, facecolor='#0F172A', edgecolor='#334155', lw=1.5))
    ax.text(99, 42, 'COMMANDS:', fontsize=7, color='#38BDF8', fontweight='bold', ha='center')
    ax.text(99, 36, '> LED ON', fontsize=7, color='#4ADE80', fontfamily='monospace', ha='center')
    ax.text(99, 31, '> LED OFF', fontsize=7, color='#F87171', fontfamily='monospace', ha='center')
    draw_resistor(ax, p['LED_EXT (PA5)'][0], 22, 74, 22, '330Ω')
    lc1 = draw_led(ax, 74, 22, '#10B981', 'EXT LED (PA5)', 'right')
    draw_gnd(ax, lc1[0] + 6, 16)
    ax.plot([lc1[0], lc1[0] + 6], [lc1[1], lc1[1]], 'k-', lw=1.5)
    save_fig(fig, 'STM32/CAT9/TASK9B')

def gen_stm32_task10a():
    fig, ax = setup_canvas('STM32 / CAT10 / TASK10A : STM32 to Wemos D1 Mini UART Bridge', 'Hardware UART Bridging: USART2 (Modem AT Interface) & USART1 (PC Debug)', 'STM32 USART2 (PA2/PA3) talks to Wemos Mini ESP8266; USART1 (PA9/PA10) bridges to PC terminal.')
    left = [('USART1_TX', 'PA9', 36), ('USART1_RX', 'PA10', 28)]
    right = [('USART2_TX', 'PA2', 36), ('USART2_RX', 'PA3', 28), ('3.3V', 'VCC', 20), ('GND', 'GND', 14)]
    p = draw_ic(ax, 34, 8, 32, 42, 'STM32F103', 'Host Controller', left_pins=left, right_pins=right)
    ax.add_patch(patches.Rectangle((8, 20), 18, 24, facecolor='#1E293B', edgecolor='#0F172A', lw=2))
    ax.text(17, 38, 'PC DEBUGGER', fontsize=8, fontweight='bold', color='white', ha='center')
    ax.text(17, 32, 'PuTTY Console', fontsize=7.5, color='#38BDF8', ha='center')
    ax.plot([26, 31.5], [36, 36], 'r-', lw=1.5)
    ax.plot([26, 31.5], [28, 28], 'b-', lw=1.5)
    w_left = [('RX (GPIO3)', 'D4', 36), ('TX (GPIO1)', 'D3', 28), ('3.3V', '3V3', 20), ('GND', 'GND', 14)]
    draw_ic(ax, 78, 8, 28, 42, 'WEMOS D1 MINI', 'ESP8266 Wi-Fi SoC', left_pins=w_left, fill='#EFF6FF', border='#1D4ED8')
    ax.plot([68.5, 75.5], [36, 36], 'r-', lw=2)
    ax.text(72, 38, 'TX->RX', fontsize=7.5, color='#DC2626', ha='center')
    ax.plot([68.5, 75.5], [28, 28], 'b-', lw=2)
    ax.text(72, 25.5, 'RX<-TX', fontsize=7.5, color='#2563EB', ha='center')
    ax.plot([68.5, 75.5], [20, 20], 'k-', lw=1.5)
    ax.plot([68.5, 75.5], [14, 14], 'k-', lw=1.5)
    save_fig(fig, 'STM32/CAT10/TASK10A')

def gen_stm32_task10b():
    fig, ax = setup_canvas('STM32 / CAT10 / TASK10B : Wemos Wi-Fi AP & Embedded Web Server', 'SoftAP Mode & HTTP Web Server Dispatching Commands to STM32 over UART', 'Clients connect to Wi-Fi SSID and send HTTP GET /led/toggle requests to actuate PC13.')
    right = [('USART2_TX (PA2)', 'A2', 34), ('USART2_RX (PA3)', 'A3', 26), ('PC13 (LED)', 'C13', 18)]
    p = draw_ic(ax, 16, 10, 30, 38, 'STM32F103', 'ARM MCU', right_pins=right)
    w_left = [('RX', 'D4', 34), ('TX', 'D3', 26)]
    draw_ic(ax, 54, 16, 22, 28, 'WEMOS D1', 'ESP8266 AP', left_pins=w_left, fill='#EFF6FF', border='#1D4ED8')
    ax.plot([48.5, 51.5], [34, 34], 'r-', lw=1.5)
    ax.plot([48.5, 51.5], [26, 26], 'b-', lw=1.5)
    ax.text(82, 38, 'Wi-Fi 802.11 b/g/n', fontsize=8, color='#0284C7', fontweight='bold', ha='center')
    for r in [6, 10, 14]:
        arc = patches.Arc((76, 28), r*2, r*2, angle=0, theta1=-45, theta2=45, color='#0284C7', lw=1.5)
        ax.add_patch(arc)
    ax.add_patch(patches.Rectangle((92, 18), 15, 24, facecolor='#1E293B', edgecolor='#0F172A', lw=2))
    ax.text(99.5, 36, 'CLIENT BROWSER', fontsize=7, fontweight='bold', color='white', ha='center')
    ax.text(99.5, 30, 'http://192.168.4.1', fontsize=6.5, color='#38BDF8', ha='center')
    ax.text(99.5, 24, 'GET /led/toggle', fontsize=6.5, color='#4ADE80', ha='center')
    draw_resistor(ax, p['PC13 (LED)'][0], 18, 48, 18, '510Ω')
    lc = draw_led(ax, 48, 18, '#3B82F6', 'PC13 LED', 'right')
    draw_gnd(ax, lc[0] + 4, 13)
    ax.plot([lc[0], lc[0] + 4], [lc[1], lc[1]], 'k-', lw=1.5)
    save_fig(fig, 'STM32/CAT10/TASK10B')

def gen_stm32_task10c():
    fig, ax = setup_canvas('STM32 / CAT10 / TASK10C : Wemos Telemetry & Node-RED Dashboard', 'Local Network Telemetry Streaming from STM32 ADC via HTTP / TCP to Node-RED', 'Periodic sensor updates pushed through Wemos Wi-Fi to a local Node-RED dashboard server.')
    left = [('ADC_IN0 (PA0)', 'A0', 30)]
    right = [('USART2_TX (PA2)', 'A2', 32), ('USART2_RX (PA3)', 'A3', 24)]
    p = draw_ic(ax, 28, 10, 30, 36, 'STM32F103', 'MCU + ADC', left_pins=left, right_pins=right)
    ax.plot([p['ADC_IN0 (PA0)'][0], 12], [30, 30], 'k-', lw=1.5)
    ax.add_patch(patches.Rectangle((4, 24), 8, 12, facecolor='#FEF08A', edgecolor='#CA8A04', lw=1.5))
    ax.text(8, 31, 'ANALOG', fontsize=7, fontweight='bold', ha='center', color='#854D0E')
    ax.text(8, 27, 'SENSOR', fontsize=7, fontweight='bold', ha='center', color='#854D0E')
    w_left = [('RX', 'D4', 32), ('TX', 'D3', 24)]
    draw_ic(ax, 66, 12, 18, 32, 'WEMOS', 'ESP8266', left_pins=w_left, fill='#EFF6FF', border='#1D4ED8')
    ax.plot([60.5, 63.5], [32, 32], 'r-', lw=1.5)
    ax.plot([60.5, 63.5], [24, 24], 'b-', lw=1.5)
    ax.add_patch(patches.Rectangle((90, 14), 18, 28, facecolor='#881337', edgecolor='#4C0519', lw=2))
    ax.text(99, 36, 'NODE-RED', fontsize=8.5, fontweight='bold', color='white', ha='center')
    ax.text(99, 30, 'Local Gateway', fontsize=7.5, color='#FECDD3', ha='center')
    ax.text(99, 22, 'Live Gauge UI', fontsize=7, color='#FECDD3', ha='center')
    ax.annotate('', xy=(90, 28), xytext=(84, 28), arrowprops=dict(arrowstyle='->', lw=2, color='#E11D48'))
    save_fig(fig, 'STM32/CAT10/TASK10C')

def gen_stm32_task11a():
    fig, ax = setup_canvas('STM32 / CAT11 / TASK11A : NUCLEO-F401RE Green LED LD2 Bring-Up', 'STM32F401RE ARM Cortex-M4 @ 84 MHz Driving User LED LD2 on PA5', 'ST-LINK/V2-1 embedded debugger provides SWD programming and Virtual COM Port.')
    left = [('SWDIO (PA13)', 'A13', 36), ('SWCLK (PA14)', 'A14', 28), ('NRST', 'RST', 20)]
    right = [('PA5 (LD2)', 'A5', 30)]
    p = draw_ic(ax, 38, 10, 36, 40, 'STM32F401RET6', 'ARM Cortex-M4 (NUCLEO-64)', left_pins=left, right_pins=right)
    draw_vcc(ax, 56, 51.5, '+3.3V')
    draw_gnd(ax, 56, 7.5, 'GND')
    s_right = [('SWDIO', '1', 36), ('SWCLK', '2', 28), ('NRST', '3', 20)]
    draw_ic(ax, 10, 12, 20, 34, 'ST-LINK/V2-1', 'On-Board Debugger', right_pins=s_right, fill='#F1F5F9', border='#334155')
    for py in [36, 28, 20]:
        ax.plot([32.5, 35.5], [py, py], 'k-', lw=1.5)
    draw_resistor(ax, p['PA5 (LD2)'][0], 30, 88, 30, '510Ω')
    lc = draw_led(ax, 88, 30, '#10B981', 'LD2 (GREEN)', 'right')
    draw_gnd(ax, lc[0] + 6, 16)
    ax.plot([lc[0], lc[0] + 6], [lc[1], lc[1]], 'k-', lw=1.5)
    save_fig(fig, 'STM32/CAT11/TASK11A')

def gen_stm32_task11b():
    fig, ax = setup_canvas('STM32 / CAT11 / TASK11B : NUCLEO User Button B1 & LD2 Control', 'User Push Button B1 on PC13 with Hardware Debounce Controlling User LED LD2 on PA5', 'Button B1 is Active LOW with on-board pull-up and filter capacitor on NUCLEO-64.')
    left = [('PC13 (USER B1)', 'C13', 30)]
    right = [('PA5 (USER LD2)', 'A5', 30)]
    p = draw_ic(ax, 36, 12, 38, 36, 'STM32F401RET6', 'NUCLEO-F401RE Board', left_pins=left, right_pins=right)
    draw_vcc(ax, 55, 49.5, '+3.3V')
    draw_gnd(ax, 55, 9.5, 'GND')
    draw_switch(ax, 12, 30, 33.5, 30, 'B1 (BLUE BUTTON)')
    draw_gnd(ax, 12, 25)
    draw_vcc(ax, 33.5, 42, '+3.3V')
    draw_resistor(ax, 33.5, 40, 33.5, 30, '4.7kΩ')
    draw_resistor(ax, p['PA5 (USER LD2)'][0], 30, 88, 30, '510Ω')
    lc = draw_led(ax, 88, 30, '#10B981', 'LD2 (GREEN)', 'right')
    draw_gnd(ax, lc[0] + 6, 16)
    ax.plot([lc[0], lc[0] + 6], [lc[1], lc[1]], 'k-', lw=1.5)
    save_fig(fig, 'STM32/CAT11/TASK11B')

def gen_stm32_task12a():
    fig, ax = setup_canvas('STM32 / CAT12 / TASK12A : BME280 I2C Hardware Bus Interface', 'Bosch Sensortec BME280 Interfaced to STM32F401RE I2C1 (PB8 SCL, PB9 SDA)', 'Both I2C bus lines require 4.7kΩ pull-up resistors to +3.3V; primary device address is 0x76.')
    right = [('I2C1_SCL (PB8)', 'B8', 36), ('I2C1_SDA (PB9)', 'B9', 24)]
    p = draw_ic(ax, 16, 10, 32, 38, 'STM32F401RE', 'ARM Cortex-M4', right_pins=right)
    draw_vcc(ax, 32, 49.5, '+3.3V')
    draw_gnd(ax, 32, 7.5, 'GND')
    draw_vcc(ax, 58, 49.5, '+3.3V')
    ax.plot([58, 58], [47.5, 44], 'k-', lw=1.5)
    ax.plot([54, 62], [44, 44], 'k-', lw=1.5)
    draw_resistor(ax, 54, 44, 54, 36, '4.7kΩ')
    draw_resistor(ax, 62, 44, 62, 24, '4.7kΩ')
    ax.plot([50.5, 75.5], [36, 36], 'k-', lw=1.5)
    ax.plot([50.5, 75.5], [24, 24], 'k-', lw=1.5)
    ax.plot([54], [36], 'ko', markersize=4)
    ax.plot([62], [24], 'ko', markersize=4)
    b_left = [('SCL', '3', 36), ('SDA', '4', 24), ('VDD', '1', 44), ('GND', '2', 14)]
    draw_ic(ax, 78, 8, 28, 42, 'BME280', 'Bosch Sensortec', left_pins=b_left, fill='#FEF3C7', border='#D97706')
    draw_vcc(ax, 75.5, 44, '+3.3V')
    draw_gnd(ax, 75.5, 12, 'GND')
    ax.text(92, 18, 'Addr: 0x76 (SDO=GND)', fontsize=7, color='#78350F', ha='center', fontweight='bold')
    save_fig(fig, 'STM32/CAT12/TASK12A')

def gen_stm32_task12b():
    fig, ax = setup_canvas('STM32 / CAT12 / TASK12B : Bosch API Wrapper & Sampling Engine', 'BME280 I2C Bus Driver + Bosch Sensor API Integration and Data Sampling', 'Reads raw uncompensated ADC values from BME280 and evaluates 64-bit calibration polynomial.')
    right = [('I2C1_SCL (PB8)', 'B8', 36), ('I2C1_SDA (PB9)', 'B9', 28)]
    p = draw_ic(ax, 16, 10, 32, 38, 'STM32F401RE', 'Host MCU', right_pins=right)
    b_left = [('SCL', '3', 36), ('SDA', '4', 28)]
    draw_ic(ax, 60, 14, 22, 30, 'BME280', 'I2C Sensor', left_pins=b_left, fill='#FEF3C7', border='#D97706')
    ax.plot([50.5, 57.5], [36, 36], 'k-', lw=1.5)
    ax.plot([50.5, 57.5], [28, 28], 'k-', lw=1.5)
    ax.add_patch(patches.Rectangle((88, 16), 18, 26, facecolor='#0F172A', edgecolor='#334155', lw=2))
    ax.text(97, 36, 'BOSCH API', fontsize=8, fontweight='bold', color='#38BDF8', ha='center')
    ax.text(97, 31, 'bme280_get_sensor_data()', fontsize=6, color='#E2E8F0', fontfamily='monospace', ha='center')
    ax.text(97, 25, 'T (°C) | P (hPa) | H (%)', fontsize=6.5, color='#4ADE80', ha='center', fontweight='bold')
    ax.plot([82, 88], [29, 29], 'k-', lw=1.5)
    save_fig(fig, 'STM32/CAT12/TASK12B')

def gen_stm32_task12c():
    fig, ax = setup_canvas('STM32 / CAT12 / TASK12C : Environmental Telemetry Streaming', 'Continuous Multi-Variable Sensor Acquisition & USART2 Serial Streaming', 'BME280 on I2C1; formatted environmental string output on USART2 (PA2/PA3) via ST-LINK VCP.')
    left = [('USART2_TX', 'PA2', 30)]
    right = [('I2C1_SCL', 'PB8', 36), ('I2C1_SDA', 'PB9', 24)]
    p = draw_ic(ax, 38, 10, 32, 38, 'STM32F401RE', 'ARM Cortex-M4', left_pins=left, right_pins=right)
    ax.add_patch(patches.Rectangle((8, 18), 20, 24, facecolor='#1E293B', edgecolor='#0F172A', lw=2))
    ax.text(18, 36, 'HOST PC', fontsize=8.5, fontweight='bold', color='white', ha='center')
    ax.text(18, 30, 'PuTTY Terminal', fontsize=7.5, color='#38BDF8', ha='center')
    ax.text(18, 24, '115200 Baud', fontsize=7, color='#94A3B8', ha='center')
    ax.plot([28, 35.5], [30, 30], 'r-', lw=2)
    b_left = [('SCL', '3', 36), ('SDA', '4', 24)]
    draw_ic(ax, 80, 10, 24, 38, 'BME280', 'Sensor Module', left_pins=b_left, fill='#FEF3C7', border='#D97706')
    ax.plot([72.5, 77.5], [36, 36], 'k-', lw=1.5)
    ax.plot([72.5, 77.5], [24, 24], 'k-', lw=1.5)
    save_fig(fig, 'STM32/CAT12/TASK12C')

def gen_stm32_task13():
    fig, ax = setup_canvas('STM32 / CAT13 / TASK13 : STM32 + ESP8266 MQTT Telemetry Gateway', 'BME280 Environmental Acquisition over I2C1 & MQTT Publish via USART2 to ESP8266', 'Publishes JSON payload {"temp":T,"press":P,"hum":H} to broker.emqx.io:1883 on stm32/test/data.')
    left = [('I2C1_SCL', 'PB8', 36), ('I2C1_SDA', 'PB9', 24)]
    right = [('USART2_TX', 'PA2', 36), ('USART2_RX', 'PA3', 24)]
    p = draw_ic(ax, 40, 10, 30, 38, 'STM32F401RE', 'Gateway Node', left_pins=left, right_pins=right)
    b_right = [('SCL', '3', 36), ('SDA', '4', 24)]
    draw_ic(ax, 10, 12, 20, 34, 'BME280', 'I2C Sensor', right_pins=b_right, fill='#FEF3C7', border='#D97706')
    ax.plot([32.5, 37.5], [36, 36], 'k-', lw=1.5)
    ax.plot([32.5, 37.5], [24, 24], 'k-', lw=1.5)
    e_left = [('RX', 'D4', 36), ('TX', 'D3', 24)]
    draw_ic(ax, 78, 10, 26, 38, 'ESP8266', 'Wemos D1 Wi-Fi', left_pins=e_left, fill='#EFF6FF', border='#1D4ED8')
    ax.plot([72.5, 75.5], [36, 36], 'r-', lw=2)
    ax.plot([72.5, 75.5], [24, 24], 'b-', lw=2)
    ax.text(91, 16, 'MQTT: broker.emqx.io', fontsize=7, color='#1E40AF', ha='center', fontweight='bold')
    save_fig(fig, 'STM32/CAT13/TASK13')

def gen_stm32_task14():
    fig, ax = setup_canvas('STM32 / CAT14 / TASK14 : Cloud IoT Dashboard & Actuator Control', 'Complete IoT System: Sensor -> MCU -> Wi-Fi -> EMQX MQTT Broker -> Node-RED UI', 'Bi-directional IoT gateway: publishes telemetry gauges and receives actuator commands for LD2.')
    ax.add_patch(patches.Rectangle((6, 14), 22, 32, facecolor='#F8FAFC', edgecolor='#0F172A', lw=2))
    ax.text(17, 41, 'STM32 + BME280', fontsize=8.5, fontweight='bold', ha='center')
    ax.text(17, 34, 'Sensor Node', fontsize=7.5, color='#475569', ha='center')
    ax.text(17, 26, 'I2C Sampling', fontsize=7, color='#0284C7', ha='center')
    ax.text(17, 18, 'Actuator: LD2', fontsize=7, color='#10B981', ha='center')
    ax.add_patch(patches.Rectangle((36, 18), 18, 24, facecolor='#EFF6FF', edgecolor='#1D4ED8', lw=2))
    ax.text(45, 36, 'ESP8266', fontsize=8.5, fontweight='bold', color='#1E40AF', ha='center')
    ax.text(45, 30, 'Wi-Fi Modem', fontsize=7.5, color='#3B82F6', ha='center')
    ax.text(45, 24, 'MQTT Client', fontsize=7, color='#1D4ED8', ha='center')
    ax.plot([28, 36], [30, 30], 'k-', lw=2)
    ax.text(32, 32, 'UART', fontsize=7, ha='center', fontweight='bold')
    ax.add_patch(patches.Circle((68, 30), 8, facecolor='#FEF3C7', edgecolor='#B45309', lw=2))
    ax.text(68, 32, 'EMQX', fontsize=8, fontweight='bold', color='#78350F', ha='center')
    ax.text(68, 28, 'BROKER', fontsize=7.5, fontweight='bold', color='#78350F', ha='center')
    ax.plot([54, 60], [30, 30], 'k-', lw=2)
    ax.text(57, 32, 'TCP', fontsize=7, ha='center', fontweight='bold')
    ax.add_patch(patches.Rectangle((84, 14), 22, 32, facecolor='#881337', edgecolor='#4C0519', lw=2))
    ax.text(95, 41, 'NODE-RED UI', fontsize=8.5, fontweight='bold', color='white', ha='center')
    ax.text(95, 34, 'Cloud Dashboard', fontsize=7.5, color='#FECDD3', ha='center')
    ax.text(95, 27, '• Temp Gauge', fontsize=6.5, color='#FFE4E6', ha='center')
    ax.text(95, 22, '• Humid Gauge', fontsize=6.5, color='#FFE4E6', ha='center')
    ax.text(95, 17, '• Press Chart', fontsize=6.5, color='#FFE4E6', ha='center')
    ax.plot([76, 84], [30, 30], 'k-', lw=2)
    ax.text(80, 32, 'WS', fontsize=7, ha='center', fontweight='bold')
    save_fig(fig, 'STM32/CAT14/TASK14')

def main():
    print('Starting circuit generation for all 28 tasks...')
    # 8051
    gen_8051_task2b()
    gen_8051_task3a()
    gen_8051_task4a()
    gen_8051_task5a()
    gen_8051_task5b1()
    gen_8051_task5b2()
    gen_8051_task5b3()
    gen_8051_task5c()
    gen_8051_task6a()
    gen_8051_task6b()
    gen_8051_task7a()
    gen_8051_task7b()
    gen_8051_task7c()
    # STM32
    gen_stm32_task8a()
    gen_stm32_task8b()
    gen_stm32_task8c()
    gen_stm32_task9a()
    gen_stm32_task9b()
    gen_stm32_task10a()
    gen_stm32_task10b()
    gen_stm32_task10c()
    gen_stm32_task11a()
    gen_stm32_task11b()
    gen_stm32_task12a()
    gen_stm32_task12b()
    gen_stm32_task12c()
    gen_stm32_task13()
    gen_stm32_task14()
    print('All 28 actual circuits generated successfully!')

if __name__ == '__main__':
    main()
