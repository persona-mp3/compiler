import { field, validators as r } from '@dwp/govuk-casa';

const DCPU = 'dcpu/dbc';
export default () => [
  // Only validate officeName if DPAD is "no"
  field('officeName')
    .validators([
      r.required.make({
        errorMsg: 'contact-details:officeName.validation.required',
      }),

      r.inArray.make({
        source: ['Dundee'],
        errorMsg: {
          summary: 'contact-details:officeName.validation.required',
          inline: 'contact-details:officeName.validation.required',
        },
      }),
    ])
    .conditions([({ journeyContext: c, waypoint: _w }) => c.data?.['business-unit'].businessUnit !== DCPU]),

  // Validate these if DPAD is "yes"
  field('officerName')
    .validators([
      r.required.make({
        errorMsg: 'contact-details:fields.officerName.required',
      }),
    ])
    .conditions([({ journeyContext: c, waypoint: _w }) => c.data['business-unit'].businessUnit === DCPU]),

  field('officerPhoneNumber')
    .validators([
      r.required.make({
        errorMsg: 'contact-details:fields.officerPhoneNumber.required',
      }),

      r.regex.make({
        pattern: /^\+?[0-9]+$/, //
        errorMsg: 'contact-details:fields.officerPhoneNumber.invalid',
      }),

      r.strlen.make({
        max: 20,
        min: 11,
        errorMsgMax: 'Officer Phone number must too long',
        errorMsgMin: 'Officer Phone Number must not be less than 11 digits',
      }),
    ])
    .conditions([({ journeyContext: c, waypoint: _w }) => c.data['business-unit'].businessUnit === DCPU]),

  field('officerFaxNumber')
    .validators([
      r.required.make({
        errorMsg: 'contact-details:fields.officerFaxNumber.required',
      }),
    ])
    .conditions([({ journeyContext: c, waypoint: _w }) => c.data['business-unit'].businessUnit === DCPU]),

  field('officerSite')
    .validators([
      r.required.make({
        errorMsg: 'contact-details:fields.officerSite.required',
      }),
    ])
    .conditions([({ journeyContext: c, waypoint: _w }) => c.data['business-unit'].businessUnit === DCPU]),

  field('officerSection')
    .validators([
      r.required.make({
        errorMsg: 'contact-details:fields.officerSection.required',
      }),
    ])
    .conditions([({ journeyContext: c, waypoint: _w }) => c.data['business-unit'].businessUnit === DCPU]),

  field('officerRoom')
    .validators([
      r.required.make({
        errorMsg: 'contact-details:fields.officerRoom.required',
      }),
    ])
    .conditions([({ journeyContext: c, waypoint: _w }) => c.data['business-unit'].businessUnit === DCPU]),

  field('areaIdentifier')
    .validators([
      r.required.make({
        errorMsg: 'contact-details:fields.areaIdentifier.required',
      }),
    ])
    .conditions([({ journeyContext: c, waypoint: _w }) => c.data['business-unit'].businessUnit === DCPU]),
];
