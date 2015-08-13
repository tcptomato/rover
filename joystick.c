#include <joystick.h>

struct js_event
{
    uint32_t time;     /* event timestamp in milliseconds */
    int16_t value;     /* value */
    uint8_t type;      /* event type */
    uint8_t number;    /* axis/button number */
};


volatile union input_events ie;

struct js_event jse;

#define JS_EVENT_BUTTON         0x01
#define JS_EVENT_AXIS           0x02
#define JS_EVENT_INIT           0x80


void* joystick_main(void *p)
{
    //  C_RESULT res;
    int fd;
    fd = open("/dev/input/js0", O_RDONLY );


    while(1)
    {
        if(read(fd,&jse,sizeof(jse))==sizeof(jse))
        {
            jse.type &= ~JS_EVENT_INIT;
            if(jse.type == JS_EVENT_AXIS)
            {
                ie.inps[jse.number] = jse.value;
//		printf("Axis %d %d\n", jse.number, jse.value);
            }
            if(jse.type == JS_EVENT_BUTTON)
            {
                ie.inps[jse.number + 6] = jse.value;
//		printf("Button %d %d\n",jse.number, jse.value);
            }
        }

    }

//    return 0;
}
