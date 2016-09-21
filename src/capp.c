#include <pcap/pcap.h>

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/variable.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <mruby/variable.h>

static struct mrb_data_type capp_type = {
    "Capp", NULL
};

static mrb_value
capp_live(mrb_state *mrb, mrb_value self) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;

    mrb_value device;
    mrb_int capture_length = 65535;
    mrb_value promiscuous = mrb_true_value();
    mrb_int timeout = 10;
    mrb_value capp;

    mrb_get_args(mrb, "S|ibi", &device, &capture_length, &promiscuous, &timeout);

    handle = pcap_open_live(mrb_string_value_cstr(mrb, &device), capture_length, 1, timeout, errbuf);

    if (handle == NULL) {
        mrb_raisef(mrb, E_RUNTIME_ERROR, "%s", errbuf);
    }

    capp = mrb_obj_value(Data_Wrap_Struct(mrb, mrb_class(mrb, self), &capp_type, handle));

    return capp;
}

void
mrb_mruby_capp_gem_init(mrb_state* mrb) {
    struct RClass *capp;

    capp = mrb_define_class(mrb, "Capp", mrb->object_class);

    MRB_SET_INSTANCE_TT(capp, MRB_TT_DATA);

    mrb_define_class_method(mrb, capp, "live", capp_live, MRB_ARGS_REQ(1) | MRB_ARGS_OPT(3));
}

void
mrb_mruby_capp_gem_final(mrb_state* mrb) {
}

