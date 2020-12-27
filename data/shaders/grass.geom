#version 330

layout (points) in;
layout (triangle_strip, max_vertices = 32) out;

uniform mat4 m_model;
uniform mat4 m_view;
uniform mat4 m_proj;
uniform float time;

void main(){
  if((m_model * gl_in[0].gl_Position).y > 0.5){
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.0,-0.3,0.0,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.0,0.7,0.0 + sin(gl_in[0].gl_Position.x + time) * 0.15,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(-0.1,-0.3,0.0,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(-0.0,-0.3,0.1,0.0));
    EmitVertex();
    EndPrimitive();

      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.5,-0.3,0.0,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.5,0.7,0.0 + sin(gl_in[0].gl_Position.x + time) * 0.15,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.4,-0.3,0.0,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.5,-0.3,0.1,0.0));
    EmitVertex();
    EndPrimitive();

      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(-0.5,-0.3,0.0,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(-0.5,0.7,0.0 + sin(gl_in[0].gl_Position.x + time) * 0.15,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(-0.4,-0.3,0.0,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(-0.5,-0.3,0.1,0.0));
    EmitVertex();
    EndPrimitive();

    gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.0,-0.3,0.5,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.0,0.7,0.5 + sin(gl_in[0].gl_Position.z + time) * 0.15,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(-0.1,-0.3,0.5,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.0,-0.3,0.5,0.0));
    EmitVertex();
    EndPrimitive();

      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.5,-0.3,0.5,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.5,0.7,0.5 + sin(gl_in[0].gl_Position.x + time) * 0.15,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.4,-0.3,0.5,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.5,-0.3,0.6,0.0));
    EmitVertex();
    EndPrimitive();

      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(-0.5,-0.3,0.5,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(-0.5,0.7,0.5 + sin(gl_in[0].gl_Position.x + time) * 0.15,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(-0.4,-0.3,0.5,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(-0.5,-0.3,0.6,0.0));
    EmitVertex();
    EndPrimitive();

    //SECOND SET

      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.25,-0.3,0.0,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.25,0.7,0.0 + sin(gl_in[0].gl_Position.z + time) * 0.15,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.15,-0.3,0.0,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.25,-0.3,0.1,0.0));
    EmitVertex();
    EndPrimitive();

    gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.0,-0.3,-0.25,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.0,0.75,-0.25 + sin(gl_in[0].gl_Position.x + time) * 0.1,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(-0.1,-0.3,-0.25,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.0,-0.3,-0.15,0.0));
    EmitVertex();
    EndPrimitive();

    gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.0,-0.3,0.25,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.0,0.7,0.25 + sin(gl_in[0].gl_Position.y + time) * 0.15,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(-0.1,-0.3,0.25,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.0,-0.3,0.35,0.0));
    EmitVertex();
    EndPrimitive();

      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.25,-0.3,0.25,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.25,0.7,0.25 + sin(gl_in[0].gl_Position.x + time) * 0.15,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.15,-0.3,0.25,0.0));
    EmitVertex();
      gl_Position = m_proj * m_view * m_model * (gl_in[0].gl_Position + vec4(0.25,-0.3,0.35,0.0));
    EmitVertex();
    EndPrimitive();

  }
}






