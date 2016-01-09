//
//  Converts NV12 to YUV420p
//
//
//

#include <stdint.h>


/**
  *
  * u: dst address of u
  * v: dst address of v
  * uv: uv interleaved input buffer
  *
  */
int interleave_to_planar
(
        uint32_t wxh,
        uint8_t *u,
        uint8_t *v,
  const uint8_t *uv
)
{
    int i;
    
    for (i = 0; i < wxh / 4; i++)
    {
        uint8_t u_data = uv[2 * i];     // fetch u data
        uint8_t v_data = uv[2 * i + 1]; // fetch v data
        
        u[i] = u_data;                  // write u data
        v[i] = v_data;                  // write v data
    }

    return 0;
}
